         }
     }
 
     *p = '\0';
 }
 
-/*
- * Extract the next tag name and value.
- * If there are no more tags, set the tag name to NULL.
- * The tag value is html decoded if dodecode is non-zero.
- * The tag value may be NULL if there is no tag value..
- *    format:
- *        [WS]<Tag>[WS]=[WS]['|"|`]<Value>[['|"|`|]|WS]
- */
-
-#define SKIP_TAG_WHITESPACE(ptr) while ((*ptr != '\0') && (apr_isspace (*ptr))) ptr++
-
-static void ap_ssi_get_tag_and_value(include_ctx_t *ctx, char **tag,
-                                     char **tag_val, int dodecode)
+static void add_include_vars(request_rec *r, const char *timefmt)
 {
-    *tag_val = NULL;
-    if (ctx->curr_tag_pos >= ctx->combined_tag + ctx->tag_length) {
-        *tag = NULL;
-        return;
-    }
+    apr_table_t *e = r->subprocess_env;
+    char *t;
 
-    *tag = ctx->curr_tag_pos;
-    if (!**tag) {
-        *tag = NULL;
-        /* finitio */
-        ctx->curr_tag_pos = ctx->combined_tag + ctx->tag_length;
-        return;
+    apr_table_setn(e, "DATE_LOCAL", LAZY_VALUE);
+    apr_table_setn(e, "DATE_GMT", LAZY_VALUE);
+    apr_table_setn(e, "LAST_MODIFIED", LAZY_VALUE);
+    apr_table_setn(e, "DOCUMENT_URI", r->uri);
+    if (r->path_info && *r->path_info) {
+        apr_table_setn(e, "DOCUMENT_PATH_INFO", r->path_info);
     }
-
-    *tag_val = ap_strchr(*tag, '=');
-    if (!*tag_val) {
-        ctx->curr_tag_pos = ctx->combined_tag + ctx->tag_length;
-        return;
+    apr_table_setn(e, "USER_NAME", LAZY_VALUE);
+    if (r->filename && (t = strrchr(r->filename, '/'))) {
+        apr_table_setn(e, "DOCUMENT_NAME", ++t);
     }
-
-    /* if it starts with '=' there was no tag name, just a value */
-    if (*tag_val == *tag) {
-        *tag = NULL;
+    else {
+        apr_table_setn(e, "DOCUMENT_NAME", r->uri);
     }
+    if (r->args) {
+        char *arg_copy = apr_pstrdup(r->pool, r->args);
 
-    *(*tag_val)++ = '\0';
-    ctx->curr_tag_pos = *tag_val + strlen(*tag_val) + 1; /* skip \0 byte */
-
-    if (dodecode) {
-        decodehtml(*tag_val);
+        ap_unescape_url(arg_copy);
+        apr_table_setn(e, "QUERY_STRING_UNESCAPED",
+                  ap_escape_shell_cmd(r->pool, arg_copy));
     }
-
-    return;
 }
 
-/* initial buffer size for power-of-two allocator in ap_ssi_parse_string */
-#define PARSE_STRING_INITIAL_SIZE 64
-
-/*
- * Do variable substitution on strings
- * (Note: If out==NULL, this function allocs a buffer for the resulting
- * string from r->pool.  The return value is the parsed string)
- */
-static char *ap_ssi_parse_string(request_rec *r, include_ctx_t *ctx, 
-                                 const char *in, char *out,
-                                 apr_size_t length, int leave_name)
+static const char *add_include_vars_lazy(request_rec *r, const char *var)
 {
-    char ch;
-    char *next;
-    char *end_out;
-    apr_size_t out_size;
-
-    /* allocate an output buffer if needed */
-    if (!out) {
-        out_size = PARSE_STRING_INITIAL_SIZE;
-        if (out_size > length) {
-            out_size = length;
+    char *val;
+    if (!strcasecmp(var, "DATE_LOCAL")) {
+        include_dir_config *conf =
+            (include_dir_config *)ap_get_module_config(r->per_dir_config,
+                                                       &include_module);
+        val = ap_ht_time(r->pool, r->request_time, conf->default_time_fmt, 0);
+    }
+    else if (!strcasecmp(var, "DATE_GMT")) {
+        include_dir_config *conf =
+            (include_dir_config *)ap_get_module_config(r->per_dir_config,
+                                                       &include_module);
+        val = ap_ht_time(r->pool, r->request_time, conf->default_time_fmt, 1);
+    }
+    else if (!strcasecmp(var, "LAST_MODIFIED")) {
+        include_dir_config *conf =
+            (include_dir_config *)ap_get_module_config(r->per_dir_config,
+                                                       &include_module);
+        val = ap_ht_time(r->pool, r->finfo.mtime, conf->default_time_fmt, 0);
+    }
+    else if (!strcasecmp(var, "USER_NAME")) {
+        if (apr_uid_name_get(&val, r->finfo.user, r->pool) != APR_SUCCESS) {
+            val = "<unknown>";
         }
-        out = apr_palloc(r->pool, out_size);
     }
     else {
-        out_size = length;
+        val = NULL;
     }
 
-    /* leave room for nul terminator */
-    end_out = out + out_size - 1;
+    if (val) {
+        apr_table_setn(r->subprocess_env, var, val);
+    }
+    return val;
+}
 
-    next = out;
-    while ((ch = *in++) != '\0') {
-        switch (ch) {
-        case '\\':
-            if (next == end_out) {
-                if (out_size < length) {
-                    /* double the buffer size */
-                    apr_size_t new_out_size = out_size * 2;
-                    apr_size_t current_length = next - out;
-                    char *new_out;
-                    if (new_out_size > length) {
-                        new_out_size = length;
-                    }
-                    new_out = apr_palloc(r->pool, new_out_size);
-                    memcpy(new_out, out, current_length);
-                    out = new_out;
-                    out_size = new_out_size;
-                    end_out = out + out_size - 1;
-                    next = out + current_length;
-                }
-                else {
-                    /* truncated */
-                    *next = '\0';
-                    return out;
-                }
-            }
-            if (*in == '$') {
-                *next++ = *in++;
-            }
-            else {
-                *next++ = ch;
-            }
-            break;
-        case '$':
-            {
-                const char *start_of_var_name;
-                char *end_of_var_name;        /* end of var name + 1 */
-                const char *expansion, *temp_end, *val;
-                char        tmp_store;
-                apr_size_t l;
-
-                /* guess that the expansion won't happen */
-                expansion = in - 1;
-                if (*in == '{') {
-                    ++in;
-                    start_of_var_name = in;
-                    in = ap_strchr_c(in, '}');
-                    if (in == NULL) {
-                        ap_log_rerror(APLOG_MARK, APLOG_ERR,
-                                      0, r, "Missing '}' on variable \"%s\"",
-                                      expansion);
-                        *next = '\0';
-                        return out;
-                    }
-                    temp_end = in;
-                    end_of_var_name = (char *)temp_end;
-                    ++in;
-                }
-                else {
-                    start_of_var_name = in;
-                    while (apr_isalnum(*in) || *in == '_') {
-                        ++in;
-                    }
-                    temp_end = in;
-                    end_of_var_name = (char *)temp_end;
-                }
-                /* what a pain, too bad there's no table_getn where you can
-                 * pass a non-nul terminated string */
-                l = end_of_var_name - start_of_var_name;
-                if (l != 0) {
-                    tmp_store        = *end_of_var_name;
-                    *end_of_var_name = '\0';
-                    val = get_include_var(r, ctx, start_of_var_name);
-                    *end_of_var_name = tmp_store;
-
-                    if (val) {
-                        expansion = val;
-                        l = strlen(expansion);
-                    }
-                    else if (leave_name) {
-                        l = in - expansion;
-                    }
-                    else {
-                        /* no expansion to be done */
-                        break;
-                    }
-                }
-                else {
-                    /* zero-length variable name causes just the $ to be 
-                     * copied */
-                    l = 1;
-                }
-                if ((next + l > end_out) && (out_size < length)) {
-                    /* increase the buffer size to accommodate l more chars */
-                    apr_size_t new_out_size = out_size;
-                    apr_size_t current_length = next - out;
-                    char *new_out;
-                    do {
-                        new_out_size *= 2;
-                    } while (new_out_size < current_length + l + 1); /* +1 for NUL */
-                    if (new_out_size > length) {
-                        new_out_size = length;
-                    }
-                    new_out = apr_palloc(r->pool, new_out_size);
-                    memcpy(new_out, out, current_length);
-                    out = new_out;
-                    out_size = new_out_size;
-                    end_out = out + out_size - 1;
-                    next = out + current_length;
-                }
-                l = ((int)l > end_out - next) ? (end_out - next) : l;
-                memcpy(next, expansion, l);
-                next += l;
-                break;
+static const char *get_include_var(const char *var, include_ctx_t *ctx)
+{
+    const char *val;
+    request_rec *r = ctx->intern->r;
+
+    if (apr_isdigit(*var) && !var[1]) {
+        apr_size_t idx = *var - '0';
+        backref_t *re = ctx->intern->re;
+
+        /* Handle $0 .. $9 from the last regex evaluated.
+         * The choice of returning NULL strings on not-found,
+         * v.s. empty strings on an empty match is deliberate.
+         */
+        if (!re) {
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                "regex capture $%" APR_SIZE_T_FMT " refers to no regex in %s",
+                idx, r->filename);
+            return NULL;
+        }
+        else {
+            if (re->nsub < idx || idx >= AP_MAX_REG_MATCH) {
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                              "regex capture $%" APR_SIZE_T_FMT
+                              " is out of range (last regex was: '%s') in %s",
+                              idx, re->rexp, r->filename);
+                return NULL;
             }
-        default:
-            if (next == end_out) {
-                if (out_size < length) {
-                    /* double the buffer size */
-                    apr_size_t new_out_size = out_size * 2;
-                    apr_size_t current_length = next - out;
-                    char *new_out;
-                    if (new_out_size > length) {
-                        new_out_size = length;
-                    }
-                    new_out = apr_palloc(r->pool, new_out_size);
-                    memcpy(new_out, out, current_length);
-                    out = new_out;
-                    out_size = new_out_size;
-                    end_out = out + out_size - 1;
-                    next = out + current_length;
-                }
-                else {
-                    /* truncated */
-                    *next = '\0';
-                    return out;
-                }
+
+            if (re->match[idx].rm_so < 0 || re->match[idx].rm_eo < 0) {
+                return NULL;
             }
-            *next++ = ch;
-            break;
+
+            val = apr_pstrmemdup(ctx->dpool, re->source + re->match[idx].rm_so,
+                                 re->match[idx].rm_eo - re->match[idx].rm_so);
+        }
+    }
+    else {
+        val = apr_table_get(r->subprocess_env, var);
+
+        if (val == LAZY_VALUE) {
+            val = add_include_vars_lazy(r, var);
         }
     }
-    *next = '\0';
-    return out;
-}
 
-/* --------------------------- Action handlers ---------------------------- */
+    return val;
+}
 
-/* ensure that path is relative, and does not contain ".." elements
- * ensentially ensure that it does not match the regex:
- * (^/|(^|/)\.\.(/|$))
- * XXX: Simply replace with apr_filepath_merge                    
+/*
+ * Do variable substitution on strings
+ *
+ * (Note: If out==NULL, this function allocs a buffer for the resulting
+ * string from ctx->pool. The return value is always the parsed string)
  */
-static int is_only_below(const char *path)
+static char *ap_ssi_parse_string(include_ctx_t *ctx, const char *in, char *out,
+                                 apr_size_t length, int leave_name)
 {
-#ifdef HAVE_DRIVE_LETTERS
-    if (path[1] == ':') 
-        return 0;
-#endif
-#ifdef NETWARE
-    if (ap_strchr_c(path, ':'))
-        return 0;
-#endif
-    if (path[0] == '/') {
-        return 0;
+    request_rec *r = ctx->intern->r;
+    result_item_t *result = NULL, *current = NULL;
+    apr_size_t outlen = 0, inlen, span;
+    char *ret = NULL, *eout = NULL;
+    const char *p;
+
+    if (out) {
+        /* sanity check, out && !length is not supported */
+        ap_assert(out && length);
+
+        ret = out;
+        eout = out + length - 1;
     }
-    while (*path) {
-        int dots = 0;
-        while (path[dots] == '.')
-            ++dots;
-#if defined(WIN32) 
-        /* If the name is canonical this is redundant
-         * but in security, redundancy is worthwhile.
-         * Does OS2 belong here (accepts ... for ..)?
-         */
-        if (dots > 1 && (!path[dots] || path[dots] == '/'))
-            return 0;
-#else
-        if (dots == 2 && (!path[dots] || path[dots] == '/'))
-            return 0;
-#endif
-        path += dots;
-        /* Advance to either the null byte at the end of the
-         * string or the character right after the next slash,
-         * whichever comes first
-         */
-        while (*path && (*path++ != '/')) {
-            continue;
+
+    span = strcspn(in, "\\$");
+    inlen = strlen(in);
+
+    /* fast exit */
+    if (inlen == span) {
+        if (out) {
+            apr_cpystrn(out, in, length);
+        }
+        else {
+            ret = apr_pstrmemdup(ctx->pool, in, (length && length <= inlen)
+                                                ? length - 1 : inlen);
         }
+
+        return ret;
     }
-    return 1;
-}
 
-static int handle_include(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                         request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                         apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    apr_bucket  *tmp_buck;
-    char *parsed_string;
-    int loglevel = APLOG_ERR;
-
-    *inserted_head = NULL;
-    if (ctx->flags & FLAG_PRINTING) {
-        while (1) {
-            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
-            if (tag_val == NULL) {
-                if (tag == NULL) {
-                    return (0);
-                }
-                else {
-                    return (1);
-                }
-            }
-            if (!strcmp(tag, "virtual") || !strcmp(tag, "file")) {
-                request_rec *rr = NULL;
-                char *error_fmt = NULL;
-                apr_status_t rc = APR_SUCCESS;
-
-                SPLIT_AND_PASS_PRETAG_BUCKETS(*bb, ctx, f->next, rc);
-                if (rc != APR_SUCCESS) {
-                    return rc;
-                }
- 
-                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
-                                                    MAX_STRING_LEN, 0);
-                if (tag[0] == 'f') {
-                    /* XXX: Port to apr_filepath_merge
-                     * be safe; only files in this directory or below allowed 
-                     */
-                    if (!is_only_below(parsed_string)) {
-                        error_fmt = "unable to include file \"%s\" "
-                                    "in parsed file %s";
-                    }
-                    else {
-                        rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
-                    }
-                }
-                else {
-                    rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
-                }
+    /* well, actually something to do */
+    p = in + span;
 
-                if (!error_fmt && rr->status != HTTP_OK) {
-                    error_fmt = "unable to include \"%s\" in parsed file %s";
-                }
+    if (out) {
+        if (span) {
+            memcpy(out, in, (out+span <= eout) ? span : (eout-out));
+            out += span;
+        }
+    }
+    else {
+        current = result = apr_palloc(ctx->dpool, sizeof(*result));
+        current->next = NULL;
+        current->string = in;
+        current->len = span;
+        outlen = span;
+    }
 
-                if (!error_fmt && (ctx->flags & FLAG_NO_EXEC) && 
-                    rr->content_type && 
-                    (strncmp(rr->content_type, "text/", 5))) {
-                    error_fmt = "unable to include potential exec \"%s\" "
-                        "in parsed file %s";
-                }
+    /* loop for specials */
+    do {
+        if ((out && out >= eout) || (length && outlen >= length)) {
+            break;
+        }
 
-                /* See the Kludge in send_parsed_file for why */
-                /* Basically, it puts a bread crumb in here, then looks */
-                /*   for the crumb later to see if its been here.       */
-                if (rr) 
-                    ap_set_module_config(rr->request_config, 
-                                         &include_module, r);
-
-                if (!error_fmt && ap_run_sub_req(rr)) {
-                    error_fmt = "unable to include \"%s\" in parsed file %s";
-                }
-                if (error_fmt) {
-                    ap_log_rerror(APLOG_MARK, loglevel,
-                                  0, r, error_fmt, tag_val, r->filename);
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                }
-                
-                /* Do *not* destroy the subrequest here; it may have allocated
-                 * variables in this r->subprocess_env in the subrequest's
-                 * r->pool, so that pool must survive as long as this request.
-                 * Yes, this is a memory leak. */
+        /* prepare next entry */
+        if (!out && current->len) {
+            current->next = apr_palloc(ctx->dpool, sizeof(*current->next));
+            current = current->next;
+            current->next = NULL;
+            current->len = 0;
+        }
+
+        /*
+         * escaped character
+         */
+        if (*p == '\\') {
+            if (out) {
+                *out++ = (p[1] == '$') ? *++p : *p;
+                ++p;
             }
             else {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "unknown parameter \"%s\" to tag include in %s",
-                            tag, r->filename);
-                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
-                return 1;
+                current->len = 1;
+                current->string = (p[1] == '$') ? ++p : p;
+                ++p;
+                ++outlen;
             }
         }
-    }
-    return 0;
-}
 
+        /*
+         * variable expansion
+         */
+        else {       /* *p == '$' */
+            const char *newp = NULL, *ep, *key = NULL;
 
-static int handle_echo(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                       apr_bucket **inserted_head)
-{
-    char       *tag       = NULL;
-    char       *tag_val   = NULL;
-    const char *echo_text = NULL;
-    apr_bucket  *tmp_buck;
-    apr_size_t e_len;
-    enum {E_NONE, E_URL, E_ENTITY} encode;
-
-    encode = E_ENTITY;
+            if (*++p == '{') {
+                ep = ap_strchr_c(++p, '}');
+                if (!ep) {
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Missing '}' on "
+                                  "variable \"%s\" in %s", p, r->filename);
+                    break;
+                }
 
-    *inserted_head = NULL;
-    if (ctx->flags & FLAG_PRINTING) {
-        while (1) {
-            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
-            if (tag_val == NULL) {
-                if (tag != NULL) {
-                    return 1;
+                if (p < ep) {
+                    key = apr_pstrmemdup(ctx->dpool, p, ep - p);
+                    newp = ep + 1;
                 }
-                else {
-                    return 0;
+                p -= 2;
+            }
+            else {
+                ep = p;
+                while (*ep == '_' || apr_isalnum(*ep)) {
+                    ++ep;
                 }
+
+                if (p < ep) {
+                    key = apr_pstrmemdup(ctx->dpool, p, ep - p);
+                    newp = ep;
+                }
+                --p;
             }
-            if (!strcmp(tag, "var")) {
-                conn_rec *c = r->connection;
-                const char *val =
-                    get_include_var(r, ctx,
-                                    ap_ssi_parse_string(r, ctx, tag_val, NULL,
-                                                        MAX_STRING_LEN, 0));
-                if (val) {
-                    switch(encode) {
-                    case E_NONE:   
-                        echo_text = val;
-                        break;
-                    case E_URL:
-                        echo_text = ap_escape_uri(r->pool, val);  
-                        break;
-                    case E_ENTITY: 
-                        echo_text = ap_escape_html(r->pool, val); 
-                        break;
-                    }
 
-                    e_len = strlen(echo_text);
-                    tmp_buck = apr_bucket_pool_create(echo_text, e_len,
-                                                      r->pool, c->bucket_alloc);
+            /* empty name results in a copy of '$' in the output string */
+            if (!key) {
+                if (out) {
+                    *out++ = *p++;
                 }
                 else {
-                    include_server_config *sconf= 
-                        ap_get_module_config(r->server->module_config,
-                                             &include_module);
-                    tmp_buck = apr_bucket_pool_create(sconf->undefinedEcho, 
-                                                      sconf->undefinedEchoLen,
-                                                      r->pool, c->bucket_alloc);
-                }
-                APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
-                if (*inserted_head == NULL) {
-                    *inserted_head = tmp_buck;
-                }
-            }
-            else if (!strcmp(tag, "encoding")) {
-                if (!strcasecmp(tag_val, "none")) encode = E_NONE;
-                else if (!strcasecmp(tag_val, "url")) encode = E_URL;
-                else if (!strcasecmp(tag_val, "entity")) encode = E_ENTITY;
-                else {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                           "unknown value \"%s\" to parameter \"encoding\" of "
-                           "tag echo in %s", tag_val, r->filename);
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                    return 1;
+                    current->len = 1;
+                    current->string = p++;
+                    ++outlen;
                 }
             }
             else {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "unknown parameter \"%s\" in tag echo of %s",
-                            tag, r->filename);
-                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
-                return 1;
-            }
-
-        }
-    }
-    return 0;
-}
+                const char *val = get_include_var(key, ctx);
+                apr_size_t len = 0;
 
-/* error and tf must point to a string with room for at 
- * least MAX_STRING_LEN characters 
- */
-static int handle_config(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                         request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                         apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    char *parsed_string;
-    apr_table_t *env = r->subprocess_env;
-
-    *inserted_head = NULL;
-    if (ctx->flags & FLAG_PRINTING) {
-        while (1) {
-            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 0);
-            if (tag_val == NULL) {
-                if (tag == NULL) {
-                    return 0;  /* Reached the end of the string. */
-                }
-                else {
-                    return 1;  /* tags must have values. */
+                if (val) {
+                    len = strlen(val);
                 }
-            }
-            if (!strcmp(tag, "errmsg")) {
-                if (ctx->error_str_override == NULL) {
-                    ctx->error_str_override = (char *)apr_palloc(ctx->pool,
-                                                              MAX_STRING_LEN);
-                    ctx->error_str = ctx->error_str_override;
-                }
-                ap_ssi_parse_string(r, ctx, tag_val, ctx->error_str_override,
-                                    MAX_STRING_LEN, 0);
-            }
-            else if (!strcmp(tag, "timefmt")) {
-                apr_time_t date = r->request_time;
-                if (ctx->time_str_override == NULL) {
-                    ctx->time_str_override = (char *)apr_palloc(ctx->pool,
-                                                              MAX_STRING_LEN);
-                    ctx->time_str = ctx->time_str_override;
-                }
-                ap_ssi_parse_string(r, ctx, tag_val, ctx->time_str_override,
-                                    MAX_STRING_LEN, 0);
-                apr_table_setn(env, "DATE_LOCAL", ap_ht_time(r->pool, date, 
-                               ctx->time_str, 0));
-                apr_table_setn(env, "DATE_GMT", ap_ht_time(r->pool, date, 
-                               ctx->time_str, 1));
-                apr_table_setn(env, "LAST_MODIFIED",
-                               ap_ht_time(r->pool, r->finfo.mtime, 
-                               ctx->time_str, 0));
-            }
-            else if (!strcmp(tag, "sizefmt")) {
-                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
-                                                    MAX_STRING_LEN, 0);
-                decodehtml(parsed_string);
-                if (!strcmp(parsed_string, "bytes")) {
-                    ctx->flags |= FLAG_SIZE_IN_BYTES;
+                else if (leave_name) {
+                    val = p;
+                    len = ep - p;
                 }
-                else if (!strcmp(parsed_string, "abbrev")) {
-                    ctx->flags &= FLAG_SIZE_ABBREV;
+
+                if (val && len) {
+                    if (out) {
+                        memcpy(out, val, (out+len <= eout) ? len : (eout-out));
+                        out += len;
+                    }
+                    else {
+                        current->len = len;
+                        current->string = val;
+                        outlen += len;
+                    }
                 }
-            }
-            else {
-                apr_bucket *tmp_buck;
 
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                              "unknown parameter \"%s\" to tag config in %s",
-                              tag, r->filename);
-                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
-                return 1;
+                p = newp;
             }
         }
-    }
-    return 0;
-}
-
-
-static int find_file(request_rec *r, const char *directive, const char *tag,
-                     char *tag_val, apr_finfo_t *finfo)
-{
-    char *to_send = tag_val;
-    request_rec *rr = NULL;
-    int ret=0;
-    char *error_fmt = NULL;
-    apr_status_t rv = APR_SUCCESS;
 
-    if (!strcmp(tag, "file")) {
-        /* XXX: Port to apr_filepath_merge
-         * be safe; only files in this directory or below allowed 
-         */
-        if (!is_only_below(tag_val)) {
-            error_fmt = "unable to access file \"%s\" "
-                        "in parsed file %s";
+        if ((out && out >= eout) || (length && outlen >= length)) {
+            break;
         }
-        else {
-            ap_getparents(tag_val);    /* get rid of any nasties */
 
-            /* note: it is okay to pass NULL for the "next filter" since
-               we never attempt to "run" this sub request. */
-            rr = ap_sub_req_lookup_file(tag_val, r, NULL);
+        /* check the remainder */
+        if (*p && (span = strcspn(p, "\\$")) > 0) {
+            if (!out && current->len) {
+                current->next = apr_palloc(ctx->dpool, sizeof(*current->next));
+                current = current->next;
+                current->next = NULL;
+            }
 
-            if (rr->status == HTTP_OK && rr->finfo.filetype != 0) {
-                to_send = rr->filename;
-                if ((rv = apr_stat(finfo, to_send, 
-                    APR_FINFO_GPROT | APR_FINFO_MIN, rr->pool)) != APR_SUCCESS
-                    && rv != APR_INCOMPLETE) {
-                    error_fmt = "unable to get information about \"%s\" "
-                        "in parsed file %s";
-                }
+            if (out) {
+                memcpy(out, p, (out+span <= eout) ? span : (eout-out));
+                out += span;
             }
             else {
-                error_fmt = "unable to lookup information about \"%s\" "
-                            "in parsed file %s";
+                current->len = span;
+                current->string = p;
+                outlen += span;
             }
-        }
 
-        if (error_fmt) {
-            ret = -1;
-            ap_log_rerror(APLOG_MARK, APLOG_ERR,
-                          rv, r, error_fmt, to_send, r->filename);
+            p += span;
         }
+    } while (p < in+inlen);
 
-        if (rr) ap_destroy_sub_req(rr);
-        
-        return ret;
-    }
-    else if (!strcmp(tag, "virtual")) {
-        /* note: it is okay to pass NULL for the "next filter" since
-           we never attempt to "run" this sub request. */
-        rr = ap_sub_req_lookup_uri(tag_val, r, NULL);
-
-        if (rr->status == HTTP_OK && rr->finfo.filetype != 0) {
-            memcpy((char *) finfo, (const char *) &rr->finfo,
-                   sizeof(rr->finfo));
-            ap_destroy_sub_req(rr);
-            return 0;
+    /* assemble result */
+    if (out) {
+        if (out > eout) {
+            *eout = '\0';
         }
         else {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                        "unable to get information about \"%s\" "
-                        "in parsed file %s",
-                        tag_val, r->filename);
-            ap_destroy_sub_req(rr);
-            return -1;
+            *out = '\0';
         }
     }
     else {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                    "unknown parameter \"%s\" to tag %s in %s",
-                    tag, directive, r->filename);
-        return -1;
-    }
-}
+        const char *ep;
 
-static int handle_fsize(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                        request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                        apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    apr_finfo_t  finfo;
-    apr_size_t  s_len;
-    apr_bucket   *tmp_buck;
-    char *parsed_string;
-
-    *inserted_head = NULL;
-    if (ctx->flags & FLAG_PRINTING) {
-        while (1) {
-            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
-            if (tag_val == NULL) {
-                if (tag == NULL) {
-                    return 0;
-                }
-                else {
-                    return 1;
-                }
-            }
-            else {
-                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
-                                                    MAX_STRING_LEN, 0);
-                if (!find_file(r, "fsize", tag, parsed_string, &finfo)) {
-                    /* XXX: if we *know* we're going to have to copy the
-                     * thing off of the stack anyway, why not palloc buff
-                     * instead of sticking it on the stack; then we can just
-                     * use a pool bucket and skip the copy
-                     */
-                    char buff[50];
-
-                    if (!(ctx->flags & FLAG_SIZE_IN_BYTES)) {
-                        apr_strfsize(finfo.size, buff);
-                        s_len = strlen (buff);
-                    }
-                    else {
-                        int l, x, pos = 0;
-                        char tmp_buff[50];
+        if (length && outlen > length) {
+            outlen = length - 1;
+        }
 
-                        apr_snprintf(tmp_buff, sizeof(tmp_buff), 
-                                     "%" APR_OFF_T_FMT, finfo.size);
-                        l = strlen(tmp_buff);    /* grrr */
-                        for (x = 0; x < l; x++) {
-                            if (x && (!((l - x) % 3))) {
-                                buff[pos++] = ',';
-                            }
-                            buff[pos++] = tmp_buff[x];
-                        }
-                        buff[pos] = '\0';
-                        s_len = pos;
-                    }
+        ret = out = apr_palloc(ctx->pool, outlen + 1);
+        ep = ret + outlen;
 
-                    tmp_buck = apr_bucket_heap_create(buff, s_len, NULL,
-                                                  r->connection->bucket_alloc);
-                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
-                    if (*inserted_head == NULL) {
-                        *inserted_head = tmp_buck;
-                    }
-                }
-                else {
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                    return 1;
-                }
+        do {
+            if (result->len) {
+                memcpy(out, result->string, (out+result->len <= ep)
+                                            ? result->len : (ep-out));
+                out += result->len;
             }
-        }
-    }
-    return 0;
-}
+            result = result->next;
+        } while (result && out < ep);
 
-static int handle_flastmod(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                           request_rec *r, ap_filter_t *f, 
-                           apr_bucket *head_ptr, apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    apr_finfo_t  finfo;
-    apr_size_t  t_len;
-    apr_bucket   *tmp_buck;
-    char *parsed_string;
-
-    *inserted_head = NULL;
-    if (ctx->flags & FLAG_PRINTING) {
-        while (1) {
-            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
-            if (tag_val == NULL) {
-                if (tag == NULL) {
-                    return 0;
-                }
-                else {
-                    return 1;
-                }
-            }
-            else {
-                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
-                                                    MAX_STRING_LEN, 0);
-                if (!find_file(r, "flastmod", tag, parsed_string, &finfo)) {
-                    char *t_val;
-
-                    t_val = ap_ht_time(r->pool, finfo.mtime, ctx->time_str, 0);
-                    t_len = strlen(t_val);
-
-                    tmp_buck = apr_bucket_pool_create(t_val, t_len, r->pool,
-                                                  r->connection->bucket_alloc);
-                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
-                    if (*inserted_head == NULL) {
-                        *inserted_head = tmp_buck;
-                    }
-                }
-                else {
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                    return 1;
-                }
-            }
-        }
+        ret[outlen] = '\0';
     }
-    return 0;
+
+    return ret;
 }
 
-static int re_check(request_rec *r, include_ctx_t *ctx, 
-                    char *string, char *rexp)
+
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |              Conditional Expression Parser
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+static APR_INLINE int re_check(include_ctx_t *ctx, const char *string,
+                               const char *rexp)
 {
-    regex_t *compiled;
-    const apr_size_t nres = sizeof(*ctx->re_result) / sizeof(regmatch_t);
-    int regex_error;
-
-    compiled = ap_pregcomp(r->pool, rexp, REG_EXTENDED | REG_NOSUB);
-    if (compiled == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      "unable to compile pattern \"%s\"", rexp);
+    ap_regex_t *compiled;
+    backref_t *re = ctx->intern->re;
+    int rc;
+
+    compiled = ap_pregcomp(ctx->dpool, rexp, AP_REG_EXTENDED);
+    if (!compiled) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->intern->r, "unable to "
+                      "compile pattern \"%s\"", rexp);
         return -1;
     }
-    if (!ctx->re_result) {
-        ctx->re_result = apr_pcalloc(r->pool, sizeof(*ctx->re_result));
+
+    if (!re) {
+        re = ctx->intern->re = apr_palloc(ctx->pool, sizeof(*re));
     }
-    ctx->re_string = string;
-    regex_error = ap_regexec(compiled, string, nres, *ctx->re_result, 0);
-    ap_pregfree(r->pool, compiled);
-    return (!regex_error);
-}
 
-enum token_type {
-    token_string, token_re,
-    token_and, token_or, token_not, token_eq, token_ne,
-    token_rbrace, token_lbrace, token_group,
-    token_ge, token_le, token_gt, token_lt
-};
-struct token {
-    enum token_type type;
-    char* value;
-};
+    re->source = apr_pstrdup(ctx->pool, string);
+    re->rexp = apr_pstrdup(ctx->pool, rexp);
+    re->nsub = compiled->re_nsub;
+    rc = !ap_regexec(compiled, string, AP_MAX_REG_MATCH, re->match, 0);
+
+    ap_pregfree(ctx->dpool, compiled);
+    return rc;
+}
 
-static const char *get_ptoken(request_rec *r, const char *string, 
-                              struct token *token, int *unmatched)
+static int get_ptoken(apr_pool_t *pool, const char **parse, token_t *token)
 {
-    char ch;
-    int next = 0;
-    char qs = 0;
-    int tkn_fnd = 0;
+    const char *p;
+    apr_size_t shift;
+    int unmatched;
 
     token->value = NULL;
 
-    /* Skip leading white space */
-    if (string == (char *) NULL) {
-        return (char *) NULL;
+    if (!*parse) {
+        return 0;
     }
-    while ((ch = *string++)) {
-        if (!apr_isspace(ch)) {
-            break;
-        }
+
+    /* Skip leading white space */
+    while (apr_isspace(**parse)) {
+        ++*parse;
     }
-    if (ch == '\0') {
-        return (char *) NULL;
+
+    if (!**parse) {
+        *parse = NULL;
+        return 0;
     }
 
-    token->type = token_string; /* the default type */
-    switch (ch) {
+    TYPE_TOKEN(token, TOKEN_STRING); /* the default type */
+    p = *parse;
+    unmatched = 0;
+
+    switch (*(*parse)++) {
     case '(':
-        token->type = token_lbrace;
-        return (string);
+        TYPE_TOKEN(token, TOKEN_LBRACE);
+        return 0;
     case ')':
-        token->type = token_rbrace;
-        return (string);
+        TYPE_TOKEN(token, TOKEN_RBRACE);
+        return 0;
     case '=':
-        token->type = token_eq;
-        return (string);
+        if (**parse == '=') ++*parse;
+        TYPE_TOKEN(token, TOKEN_EQ);
+        return 0;
     case '!':
-        if (*string == '=') {
-            token->type = token_ne;
-            return (string + 1);
-        }
-        else {
-            token->type = token_not;
-            return (string);
+        if (**parse == '=') {
+            TYPE_TOKEN(token, TOKEN_NE);
+            ++*parse;
+            return 0;
         }
+        TYPE_TOKEN(token, TOKEN_NOT);
+        return 0;
     case '\'':
-        /* already token->type == token_string */
-        qs = '\'';
+        unmatched = '\'';
         break;
     case '/':
-        token->type = token_re;
-        qs = '/';
+        TYPE_TOKEN(token, TOKEN_RE);
+        unmatched = '/';
         break;
     case '|':
-        if (*string == '|') {
-            token->type = token_or;
-            return (string + 1);
+        if (**parse == '|') {
+            TYPE_TOKEN(token, TOKEN_OR);
+            ++*parse;
+            return 0;
         }
         break;
     case '&':
-        if (*string == '&') {
-            token->type = token_and;
-            return (string + 1);
+        if (**parse == '&') {
+            TYPE_TOKEN(token, TOKEN_AND);
+            ++*parse;
+            return 0;
         }
         break;
     case '>':
-        if (*string == '=') {
-            token->type = token_ge;
-            return (string + 1);
-        }
-        else {
-            token->type = token_gt;
-            return (string);
+        if (**parse == '=') {
+            TYPE_TOKEN(token, TOKEN_GE);
+            ++*parse;
+            return 0;
         }
+        TYPE_TOKEN(token, TOKEN_GT);
+        return 0;
     case '<':
-        if (*string == '=') {
-            token->type = token_le;
-            return (string + 1);
-        }
-        else {
-            token->type = token_lt;
-            return (string);
+        if (**parse == '=') {
+            TYPE_TOKEN(token, TOKEN_LE);
+            ++*parse;
+            return 0;
         }
-    default:
-        /* already token->type == token_string */
-        break;
-    }
-    /* We should only be here if we are in a string */
-    token->value = apr_palloc(r->pool, strlen(string) + 2); /* 2 for ch plus
-                                                               trailing null */
-    if (!qs) {
-        --string;
+        TYPE_TOKEN(token, TOKEN_LT);
+        return 0;
     }
 
-    /* 
-     * I used the ++string throughout this section so that string
-     * ends up pointing to the next token and I can just return it
+    /* It's a string or regex token
+     * Now search for the next token, which finishes this string
      */
-    for (ch = *string; ((ch != '\0') && (!tkn_fnd)); ch = *++string) {
-        if (ch == '\\') {
-            if ((ch = *++string) == '\0') {
-                tkn_fnd = 1;
-            }
-            else {
-                token->value[next++] = ch;
+    shift = 0;
+    p = *parse = token->value = unmatched ? *parse : p;
+
+    for (; **parse; p = ++*parse) {
+        if (**parse == '\\') {
+            if (!*(++*parse)) {
+                p = *parse;
+                break;
             }
+
+            ++shift;
         }
         else {
-            if (!qs) {
-                if (apr_isspace(ch)) {
-                    tkn_fnd = 1;
-                }
-                else {
-                    switch (ch) {
-                    case '(':
-                    case ')':
-                    case '=':
-                    case '!':
-                    case '<':
-                    case '>':
-                        tkn_fnd = 1;
-                        break;
-                    case '|':
-                        if (*(string + 1) == '|') {
-                            tkn_fnd = 1;
-                        }
-                        break;
-                    case '&':
-                        if (*(string + 1) == '&') {
-                            tkn_fnd = 1;
-                        }
-                        break;
-                    }
-                    if (!tkn_fnd) {
-                        token->value[next++] = ch;
-                    }
+            if (unmatched) {
+                if (**parse == unmatched) {
+                    unmatched = 0;
+                    ++*parse;
+                    break;
                 }
+            } else if (apr_isspace(**parse)) {
+                break;
             }
             else {
-                if (ch == qs) {
-                    qs = 0;
-                    tkn_fnd = 1;
-                    string++;
+                int found = 0;
+
+                switch (**parse) {
+                case '(':
+                case ')':
+                case '=':
+                case '!':
+                case '<':
+                case '>':
+                    ++found;
+                    break;
+
+                case '|':
+                case '&':
+                    if ((*parse)[1] == **parse) {
+                        ++found;
+                    }
+                    break;
                 }
-                else {
-                    token->value[next++] = ch;
+
+                if (found) {
+                    break;
                 }
             }
         }
-        if (tkn_fnd) {
-            break;
-        }
     }
 
-    /* If qs is still set, we have an unmatched quote */
-    if (qs) {
-        *unmatched = 1;
-        next = 0;
+    if (unmatched) {
+        token->value = apr_pstrdup(pool, "");
     }
-    token->value[next] = '\0';
+    else {
+        apr_size_t len = p - token->value - shift;
+        char *c = apr_palloc(pool, len + 1);
 
-    return (string);
-}
+        p = token->value;
+        token->value = c;
 
+        while (shift--) {
+            const char *e = ap_strchr_c(p, '\\');
 
-/* there is an implicit assumption here that expr is at most MAX_STRING_LEN-1
- * characters long...
- */
-static int parse_expr(request_rec *r, include_ctx_t *ctx, const char *expr,
-                      int *was_error, int *was_unmatched, char *debug)
+            memcpy(c, p, e-p);
+            c   += e-p;
+            *c++ = *++e;
+            len -= e-p;
+            p    = e+1;
+        }
+
+        if (len) {
+            memcpy(c, p, len);
+        }
+        c[len] = '\0';
+    }
+
+    return unmatched;
+}
+
+static int parse_expr(include_ctx_t *ctx, const char *expr, int *was_error)
 {
-    struct parse_node {
-        struct parse_node *left, *right, *parent;
-        struct token token;
-        int value, done;
-    } *root, *current, *new;
-    const char *parse;
-    char* buffer;
-    int retval = 0;
-    apr_size_t debug_pos = 0;
+    parse_node_t *new, *root = NULL, *current = NULL;
+    request_rec *r = ctx->intern->r;
+    const char *error = "Invalid expression \"%s\" in file %s";
+    const char *parse = expr;
+    int was_unmatched = 0;
+    unsigned regex = 0;
 
-    debug[debug_pos] = '\0';
-    *was_error       = 0;
-    *was_unmatched   = 0;
-    if ((parse = expr) == (char *) NULL) {
-        return (0);
+    *was_error = 0;
+
+    if (!parse) {
+        return 0;
     }
-    root = current = (struct parse_node *) NULL;
 
     /* Create Parse Tree */
     while (1) {
-        new = (struct parse_node *) apr_palloc(r->pool,
-                                           sizeof(struct parse_node));
-        new->parent = new->left = new->right = (struct parse_node *) NULL;
-        new->done = 0;
-        if ((parse = get_ptoken(r, parse, &new->token, was_unmatched)) == 
-            (char *) NULL) {
+        /* uncomment this to see how the tree a built:
+         *
+         * DEBUG_DUMP_TREE(ctx, root);
+         */
+        CREATE_NODE(ctx, new);
+
+        was_unmatched = get_ptoken(ctx->dpool, &parse, &new->token);
+        if (!parse) {
             break;
         }
-        switch (new->token.type) {
 
-        case token_string:
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos], 
-                                  "     Token: string (%s)\n", 
-                                  new->token.value);
-#endif
-            if (current == (struct parse_node *) NULL) {
+        DEBUG_DUMP_UNMATCHED(ctx, was_unmatched);
+        DEBUG_DUMP_TOKEN(ctx, &new->token);
+
+        if (!current) {
+            switch (new->token.type) {
+            case TOKEN_STRING:
+            case TOKEN_NOT:
+            case TOKEN_LBRACE:
                 root = current = new;
-                break;
+                continue;
+
+            default:
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr,
+                              r->filename);
+                *was_error = 1;
+                return 0;
             }
+        }
+
+        switch (new->token.type) {
+        case TOKEN_STRING:
             switch (current->token.type) {
-            case token_string:
-                current->token.value = apr_pstrcat(r->pool,
-                                                   current->token.value,
-                                                   current->token.value[0] ? " " : "",
-                                                   new->token.value,
-                                                   NULL);
-                                                   
+            case TOKEN_STRING:
+                current->token.value =
+                    apr_pstrcat(ctx->dpool, current->token.value,
+                                *current->token.value ? " " : "",
+                                new->token.value, NULL);
+                continue;
+
+            case TOKEN_RE:
+            case TOKEN_RBRACE:
+            case TOKEN_GROUP:
                 break;
-            case token_eq:
-            case token_ne:
-            case token_and:
-            case token_or:
-            case token_lbrace:
-            case token_not:
-            case token_ge:
-            case token_gt:
-            case token_le:
-            case token_lt:
+
+            default:
                 new->parent = current;
                 current = current->right = new;
-                break;
-            default:
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "Invalid expression \"%s\" in file %s",
-                            expr, r->filename);
-                *was_error = 1;
-                return retval;
+                continue;
             }
             break;
 
-        case token_re:
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos], 
-                                  "     Token: regex (%s)\n", 
-                                  new->token.value);
-#endif
-            if (current == (struct parse_node *) NULL) {
-                root = current = new;
-                break;
-            }
+        case TOKEN_RE:
             switch (current->token.type) {
-            case token_eq:
-            case token_ne:
-            case token_and:
-            case token_or:
-            case token_lbrace:
-            case token_not:
+            case TOKEN_EQ:
+            case TOKEN_NE:
                 new->parent = current;
                 current = current->right = new;
-                break;
+                ++regex;
+                continue;
+
             default:
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "Invalid expression \"%s\" in file %s",
-                            expr, r->filename);
-                *was_error = 1;
-                return retval;
+                break;
             }
             break;
 
-        case token_and:
-        case token_or:
-#ifdef DEBUG_INCLUDE
-            memcpy (&debug[debug_pos], "     Token: and/or\n",
-                    sizeof ("     Token: and/or\n"));
-            debug_pos += sizeof ("     Token: and/or\n");
-#endif
-            if (current == (struct parse_node *) NULL) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "Invalid expression \"%s\" in file %s",
-                            expr, r->filename);
-                *was_error = 1;
-                return retval;
-            }
-            /* Percolate upwards */
-            while (current != (struct parse_node *) NULL) {
-                switch (current->token.type) {
-                case token_string:
-                case token_re:
-                case token_group:
-                case token_not:
-                case token_eq:
-                case token_ne:
-                case token_and:
-                case token_or:
-                case token_ge:
-                case token_gt:
-                case token_le:
-                case token_lt:
-                    current = current->parent;
-                    continue;
-                case token_lbrace:
+        case TOKEN_AND:
+        case TOKEN_OR:
+            switch (current->token.type) {
+            case TOKEN_STRING:
+            case TOKEN_RE:
+            case TOKEN_GROUP:
+                current = current->parent;
+
+                while (current) {
+                    switch (current->token.type) {
+                    case TOKEN_AND:
+                    case TOKEN_OR:
+                    case TOKEN_LBRACE:
+                        break;
+
+                    default:
+                        current = current->parent;
+                        continue;
+                    }
                     break;
-                default:
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                "Invalid expression \"%s\" in file %s",
-                                expr, r->filename);
-                    *was_error = 1;
-                    return retval;
                 }
-                break;
-            }
-            if (current == (struct parse_node *) NULL) {
-                new->left = root;
-                new->left->parent = new;
-                new->parent = (struct parse_node *) NULL;
-                root = new;
-            }
-            else {
+
+                if (!current) {
+                    new->left = root;
+                    root->parent = new;
+                    current = root = new;
+                    continue;
+                }
+
                 new->left = current->right;
                 new->left->parent = new;
-                current->right = new;
                 new->parent = current;
-            }
-            current = new;
-            break;
+                current = current->right = new;
+                continue;
 
-        case token_not:
-#ifdef DEBUG_INCLUDE
-            memcpy(&debug[debug_pos], "     Token: not\n",
-                    sizeof("     Token: not\n"));
-            debug_pos += sizeof("     Token: not\n");
-#endif
-            if (current == (struct parse_node *) NULL) {
-                root = current = new;
+            default:
                 break;
             }
-            /* Percolate upwards */
-            if (current != (struct parse_node *) NULL) {
-                switch (current->token.type) {
-                case token_not:
-                case token_eq:
-                case token_ne:
-                case token_and:
-                case token_or:
-                case token_lbrace:
-                case token_ge:
-                case token_gt:
-                case token_le:
-                case token_lt:
-                    break;
-                default:
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                  "Invalid expression \"%s\" in file %s",
-                                  expr, r->filename);
-                    *was_error = 1;
-                    return retval;
-                }
-            }
-            if (current == (struct parse_node *) NULL) {
-                new->left = root;
-                new->left->parent = new;
-                new->parent = (struct parse_node *) NULL;
-                root = new;
-            }
-            else {
-                new->left = current->right;
-                current->right = new;
-                new->parent = current;
-            }
-            current = new;
             break;
 
-        case token_eq:
-        case token_ne:
-        case token_ge:
-        case token_gt:
-        case token_le:
-        case token_lt:
-#ifdef DEBUG_INCLUDE
-            memcpy(&debug[debug_pos], "     Token: eq/ne/ge/gt/le/lt\n",
-                    sizeof("     Token: eq/ne/ge/gt/le/lt\n"));
-            debug_pos += sizeof("     Token: eq/ne/ge/gt/le/lt\n");
-#endif
-            if (current == (struct parse_node *) NULL) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                              "Invalid expression \"%s\" in file %s",
-                              expr, r->filename);
-                *was_error = 1;
-                return retval;
-            }
-            /* Percolate upwards */
-            while (current != (struct parse_node *) NULL) {
+        case TOKEN_EQ:
+        case TOKEN_NE:
+        case TOKEN_GE:
+        case TOKEN_GT:
+        case TOKEN_LE:
+        case TOKEN_LT:
+            if (current->token.type == TOKEN_STRING) {
+                current = current->parent;
+
+                if (!current) {
+                    new->left = root;
+                    root->parent = new;
+                    current = root = new;
+                    continue;
+                }
+
                 switch (current->token.type) {
-                case token_string:
-                case token_re:
-                case token_group:
-                    current = current->parent;
+                case TOKEN_LBRACE:
+                case TOKEN_AND:
+                case TOKEN_OR:
+                    new->left = current->right;
+                    new->left->parent = new;
+                    new->parent = current;
+                    current = current->right = new;
                     continue;
-                case token_lbrace:
-                case token_and:
-                case token_or:
-                    break;
-                case token_not:
-                case token_eq:
-                case token_ne:
-                case token_ge:
-                case token_gt:
-                case token_le:
-                case token_lt:
+
                 default:
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                "Invalid expression \"%s\" in file %s",
-                                expr, r->filename);
-                    *was_error = 1;
-                    return retval;
+                    break;
                 }
-                break;
-            }
-            if (current == (struct parse_node *) NULL) {
-                new->left = root;
-                new->left->parent = new;
-                new->parent = (struct parse_node *) NULL;
-                root = new;
-            }
-            else {
-                new->left = current->right;
-                new->left->parent = new;
-                current->right = new;
-                new->parent = current;
             }
-            current = new;
             break;
 
-        case token_rbrace:
-#ifdef DEBUG_INCLUDE
-            memcpy (&debug[debug_pos], "     Token: rbrace\n",
-                    sizeof ("     Token: rbrace\n"));
-            debug_pos += sizeof ("     Token: rbrace\n");
-#endif
-            while (current != (struct parse_node *) NULL) {
-                if (current->token.type == token_lbrace) {
-                    current->token.type = token_group;
-                    break;
-                }
+        case TOKEN_RBRACE:
+            while (current && current->token.type != TOKEN_LBRACE) {
                 current = current->parent;
             }
-            if (current == (struct parse_node *) NULL) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "Unmatched ')' in \"%s\" in file %s",
-                            expr, r->filename);
-                *was_error = 1;
-                return retval;
+
+            if (current) {
+                TYPE_TOKEN(&current->token, TOKEN_GROUP);
+                continue;
             }
+
+            error = "Unmatched ')' in \"%s\" in file %s";
             break;
 
-        case token_lbrace:
-#ifdef DEBUG_INCLUDE
-            memcpy (&debug[debug_pos], "     Token: lbrace\n",
-                    sizeof ("     Token: lbrace\n"));
-            debug_pos += sizeof ("     Token: lbrace\n");
-#endif
-            if (current == (struct parse_node *) NULL) {
-                root = current = new;
+        case TOKEN_NOT:
+        case TOKEN_LBRACE:
+            switch (current->token.type) {
+            case TOKEN_STRING:
+            case TOKEN_RE:
+            case TOKEN_RBRACE:
+            case TOKEN_GROUP:
                 break;
-            }
-            /* Percolate upwards */
-            if (current != (struct parse_node *) NULL) {
-                switch (current->token.type) {
-                case token_not:
-                case token_eq:
-                case token_ne:
-                case token_and:
-                case token_or:
-                case token_lbrace:
-                case token_ge:
-                case token_gt:
-                case token_le:
-                case token_lt:
-                    break;
-                case token_string:
-                case token_re:
-                case token_group:
-                default:
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                "Invalid expression \"%s\" in file %s",
-                                expr, r->filename);
-                    *was_error = 1;
-                    return retval;
-                }
-            }
-            if (current == (struct parse_node *) NULL) {
-                new->left = root;
-                new->left->parent = new;
-                new->parent = (struct parse_node *) NULL;
-                root = new;
-            }
-            else {
-                new->left = current->right;
+
+            default:
                 current->right = new;
                 new->parent = current;
+                current = new;
+                continue;
             }
-            current = new;
             break;
+
         default:
             break;
         }
+
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr, r->filename);
+        *was_error = 1;
+        return 0;
     }
 
+    DEBUG_DUMP_TREE(ctx, root);
+
     /* Evaluate Parse Tree */
     current = root;
-    while (current != (struct parse_node *) NULL) {
+    error = NULL;
+    while (current) {
         switch (current->token.type) {
-        case token_string:
-#ifdef DEBUG_INCLUDE
-            memcpy (&debug[debug_pos], "     Evaluate string\n",
-                    sizeof ("     Evaluate string\n"));
-            debug_pos += sizeof ("     Evaluate string\n");
-#endif
-            buffer = ap_ssi_parse_string(r, ctx, current->token.value, NULL, 
-                                         MAX_STRING_LEN, 0);
-            current->token.value = buffer;
-            current->value = (current->token.value[0] != '\0');
-            current->done = 1;
-            current = current->parent;
+        case TOKEN_STRING:
+            current->token.value =
+                ap_ssi_parse_string(ctx, current->token.value, NULL, 0,
+                                    SSI_EXPAND_DROP_NAME);
+            current->value = !!*current->token.value;
             break;
 
-        case token_re:
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "No operator before regex of expr \"%s\" in file %s",
-                          expr, r->filename);
-            *was_error = 1;
-            return retval;
-
-        case token_and:
-        case token_or:
-#ifdef DEBUG_INCLUDE
-            memcpy(&debug[debug_pos], "     Evaluate and/or\n",
-                    sizeof("     Evaluate and/or\n"));
-            debug_pos += sizeof("     Evaluate and/or\n");
-#endif
-            if (current->left  == (struct parse_node *) NULL ||
-                current->right == (struct parse_node *) NULL) {
+        case TOKEN_AND:
+        case TOKEN_OR:
+            if (!current->left || !current->right) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                               "Invalid expression \"%s\" in file %s",
                               expr, r->filename);
                 *was_error = 1;
-                return retval;
+                return 0;
             }
+
             if (!current->left->done) {
                 switch (current->left->token.type) {
-                case token_string:
-                    buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
-                                                 NULL, MAX_STRING_LEN, 0);
-                    current->left->token.value = buffer;
-                    current->left->value = 
-                                       (current->left->token.value[0] != '\0');
+                case TOKEN_STRING:
+                    current->left->token.value =
+                        ap_ssi_parse_string(ctx, current->left->token.value,
+                                            NULL, 0, SSI_EXPAND_DROP_NAME);
+                    current->left->value = !!*current->left->token.value;
+                    DEBUG_DUMP_EVAL(ctx, current->left);
                     current->left->done = 1;
                     break;
+
                 default:
                     current = current->left;
                     continue;
                 }
             }
-            if (!current->right->done) {
-                switch (current->right->token.type) {
-                case token_string:
-                    buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
-                                                 NULL, MAX_STRING_LEN, 0);
-                    current->right->token.value = buffer;
-                    current->right->value = 
-                                      (current->right->token.value[0] != '\0');
-                    current->right->done = 1;
-                    break;
-                default:
-                    current = current->right;
-                    continue;
-                }
-            }
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos], "     Left: %c\n",
-                                  current->left->value ? '1' : '0');
-            debug_pos += sprintf (&debug[debug_pos], "     Right: %c\n",
-                                  current->right->value ? '1' : '0');
-#endif
-            if (current->token.type == token_and) {
-                current->value = current->left->value && current->right->value;
+
+            /* short circuit evaluation */
+            if (!current->right->done && !regex &&
+                ((current->token.type == TOKEN_AND && !current->left->value) ||
+                (current->token.type == TOKEN_OR && current->left->value))) {
+                current->value = current->left->value;
             }
             else {
-                current->value = current->left->value || current->right->value;
+                if (!current->right->done) {
+                    switch (current->right->token.type) {
+                    case TOKEN_STRING:
+                        current->right->token.value =
+                            ap_ssi_parse_string(ctx,current->right->token.value,
+                                                NULL, 0, SSI_EXPAND_DROP_NAME);
+                        current->right->value = !!*current->right->token.value;
+                        DEBUG_DUMP_EVAL(ctx, current->right);
+                        current->right->done = 1;
+                        break;
+
+                    default:
+                        current = current->right;
+                        continue;
+                    }
+                }
+
+                if (current->token.type == TOKEN_AND) {
+                    current->value = current->left->value &&
+                                     current->right->value;
+                }
+                else {
+                    current->value = current->left->value ||
+                                     current->right->value;
+                }
             }
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
-                                  current->value ? '1' : '0');
-#endif
-            current->done = 1;
-            current = current->parent;
             break;
 
-        case token_eq:
-        case token_ne:
-#ifdef DEBUG_INCLUDE
-            memcpy (&debug[debug_pos], "     Evaluate eq/ne\n",
-                    sizeof ("     Evaluate eq/ne\n"));
-            debug_pos += sizeof ("     Evaluate eq/ne\n");
-#endif
-            if ((current->left == (struct parse_node *) NULL) ||
-                (current->right == (struct parse_node *) NULL) ||
-                (current->left->token.type != token_string) ||
-                ((current->right->token.type != token_string) &&
-                 (current->right->token.type != token_re))) {
+        case TOKEN_EQ:
+        case TOKEN_NE:
+            if (!current->left || !current->right ||
+                current->left->token.type != TOKEN_STRING ||
+                (current->right->token.type != TOKEN_STRING &&
+                 current->right->token.type != TOKEN_RE)) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "Invalid expression \"%s\" in file %s",
                             expr, r->filename);
                 *was_error = 1;
-                return retval;
+                return 0;
             }
-            buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
-                                         NULL, MAX_STRING_LEN, 0);
-            current->left->token.value = buffer;
-            buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
-                                         NULL, MAX_STRING_LEN, 0);
-            current->right->token.value = buffer;
-            if (current->right->token.type == token_re) {
-#ifdef DEBUG_INCLUDE
-                debug_pos += sprintf (&debug[debug_pos],
-                                      "     Re Compare (%s) with /%s/\n",
-                                      current->left->token.value,
-                                      current->right->token.value);
-#endif
-                current->value =
-                    re_check(r, ctx, current->left->token.value,
-                             current->right->token.value);
+            current->left->token.value =
+                ap_ssi_parse_string(ctx, current->left->token.value, NULL, 0,
+                                    SSI_EXPAND_DROP_NAME);
+            current->right->token.value =
+                ap_ssi_parse_string(ctx, current->right->token.value, NULL, 0,
+                                    SSI_EXPAND_DROP_NAME);
+
+            if (current->right->token.type == TOKEN_RE) {
+                current->value = re_check(ctx, current->left->token.value,
+                                          current->right->token.value);
+                --regex;
             }
             else {
-#ifdef DEBUG_INCLUDE
-                debug_pos += sprintf (&debug[debug_pos],
-                                      "     Compare (%s) with (%s)\n",
-                                      current->left->token.value,
-                                      current->right->token.value);
-#endif
-                current->value =
-                    (strcmp(current->left->token.value,
-                            current->right->token.value) == 0);
+                current->value = !strcmp(current->left->token.value,
+                                         current->right->token.value);
             }
-            if (current->token.type == token_ne) {
+
+            if (current->token.type == TOKEN_NE) {
                 current->value = !current->value;
             }
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
-                                  current->value ? '1' : '0');
-#endif
-            current->done = 1;
-            current = current->parent;
             break;
-        case token_ge:
-        case token_gt:
-        case token_le:
-        case token_lt:
-#ifdef DEBUG_INCLUDE
-            memcpy (&debug[debug_pos], "     Evaluate ge/gt/le/lt\n",
-                    sizeof ("     Evaluate ge/gt/le/lt\n"));
-            debug_pos += sizeof ("     Evaluate ge/gt/le/lt\n");
-#endif
-            if ((current->left == (struct parse_node *) NULL) ||
-                (current->right == (struct parse_node *) NULL) ||
-                (current->left->token.type != token_string) ||
-                (current->right->token.type != token_string)) {
+
+        case TOKEN_GE:
+        case TOKEN_GT:
+        case TOKEN_LE:
+        case TOKEN_LT:
+            if (!current->left || !current->right ||
+                current->left->token.type != TOKEN_STRING ||
+                current->right->token.type != TOKEN_STRING) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "Invalid expression \"%s\" in file %s",
-                            expr, r->filename);
+                              "Invalid expression \"%s\" in file %s",
+                              expr, r->filename);
                 *was_error = 1;
-                return retval;
+                return 0;
             }
-            buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
-                                         NULL, MAX_STRING_LEN, 0);
-            current->left->token.value = buffer;
-            buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
-                                         NULL, MAX_STRING_LEN, 0);
-            current->right->token.value = buffer;
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos],
-                                  "     Compare (%s) with (%s)\n",
-                                  current->left->token.value,
-                                  current->right->token.value);
-#endif
-            current->value =
-                strcmp(current->left->token.value,
-                       current->right->token.value);
-            if (current->token.type == token_ge) {
-                current->value = current->value >= 0;
-            }
-            else if (current->token.type == token_gt) {
-                current->value = current->value > 0;
-            }
-            else if (current->token.type == token_le) {
-                current->value = current->value <= 0;
-            }
-            else if (current->token.type == token_lt) {
-                current->value = current->value < 0;
-            }
-            else {
-                current->value = 0;     /* Don't return -1 if unknown token */
-            }
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
-                                  current->value ? '1' : '0');
-#endif
-            current->done = 1;
-            current = current->parent;
-            break;
 
-        case token_not:
-            if (current->right != (struct parse_node *) NULL) {
-                if (!current->right->done) {
-                    current = current->right;
-                    continue;
-                }
-                current->value = !current->right->value;
-            }
-            else {
-                current->value = 0;
+            current->left->token.value =
+                ap_ssi_parse_string(ctx, current->left->token.value, NULL, 0,
+                                    SSI_EXPAND_DROP_NAME);
+            current->right->token.value =
+                ap_ssi_parse_string(ctx, current->right->token.value, NULL, 0,
+                                    SSI_EXPAND_DROP_NAME);
+
+            current->value = strcmp(current->left->token.value,
+                                    current->right->token.value);
+
+            switch (current->token.type) {
+            case TOKEN_GE: current->value = current->value >= 0; break;
+            case TOKEN_GT: current->value = current->value >  0; break;
+            case TOKEN_LE: current->value = current->value <= 0; break;
+            case TOKEN_LT: current->value = current->value <  0; break;
+            default: current->value = 0; break; /* should not happen */
             }
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos], "     Evaluate !: %c\n",
-                                  current->value ? '1' : '0');
-#endif
-            current->done = 1;
-            current = current->parent;
             break;
 
-        case token_group:
-            if (current->right != (struct parse_node *) NULL) {
+        case TOKEN_NOT:
+        case TOKEN_GROUP:
+            if (current->right) {
                 if (!current->right->done) {
                     current = current->right;
                     continue;
                 }
                 current->value = current->right->value;
             }
             else {
                 current->value = 1;
             }
-#ifdef DEBUG_INCLUDE
-            debug_pos += sprintf (&debug[debug_pos], "     Evaluate (): %c\n",
-                                  current->value ? '1' : '0');
-#endif
-            current->done = 1;
-            current = current->parent;
-            break;
-
-        case token_lbrace:
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                        "Unmatched '(' in \"%s\" in file %s",
-                        expr, r->filename);
-            *was_error = 1;
-            return retval;
 
-        case token_rbrace:
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                        "Unmatched ')' in \"%s\" in file %s",
-                        expr, r->filename);
-            *was_error = 1;
-            return retval;
+            if (current->token.type == TOKEN_NOT) {
+                current->value = !current->value;
+            }
+            break;
 
+        case TOKEN_RE:
+            if (!error) {
+                error = "No operator before regex in expr \"%s\" in file %s";
+            }
+        case TOKEN_LBRACE:
+            if (!error) {
+                error = "Unmatched '(' in \"%s\" in file %s";
+            }
         default:
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "bad token type");
+            if (!error) {
+                error = "internal parser error in \"%s\" in file %s";
+            }
+
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr,r->filename);
             *was_error = 1;
-            return retval;
+            return 0;
         }
+
+        DEBUG_DUMP_EVAL(ctx, current);
+        current->done = 1;
+        current = current->parent;
     }
 
-    retval = (root == (struct parse_node *) NULL) ? 0 : root->value;
-    return (retval);
+    return (root ? root->value : 0);
 }
 
-/*-------------------------------------------------------------------------*/
-#ifdef DEBUG_INCLUDE
 
-#define MAX_DEBUG_SIZE MAX_STRING_LEN
-#define LOG_COND_STATUS(cntx, t_buck, h_ptr, ins_head, tag_text)           \
-{                                                                          \
-    char cond_txt[] = "**** X     conditional_status=\"0\"\n";             \
-                                                                           \
-    if (cntx->flags & FLAG_COND_TRUE) {                                    \
-        cond_txt[31] = '1';                                                \
-    }                                                                      \
-    memcpy(&cond_txt[5], tag_text, sizeof(tag_text)-1);                    \
-    t_buck = apr_bucket_heap_create(cond_txt, sizeof(cond_txt)-1,          \
-                                    NULL, h_ptr->list);                    \
-    APR_BUCKET_INSERT_BEFORE(h_ptr, t_buck);                               \
-                                                                           \
-    if (ins_head == NULL) {                                                \
-        ins_head = t_buck;                                                 \
-    }                                                                      \
-}
-#define DUMP_PARSE_EXPR_DEBUG(t_buck, h_ptr, d_buf, ins_head)            \
-{                                                                        \
-    if (d_buf[0] != '\0') {                                              \
-        t_buck = apr_bucket_heap_create(d_buf, strlen(d_buf),            \
-                                        NULL, h_ptr->list);              \
-        APR_BUCKET_INSERT_BEFORE(h_ptr, t_buck);                         \
-                                                                         \
-        if (ins_head == NULL) {                                          \
-            ins_head = t_buck;                                           \
-        }                                                                \
-    }                                                                    \
-}
-#else
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                    Action Handlers
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+/*
+ * Extract the next tag name and value.
+ * If there are no more tags, set the tag name to NULL.
+ * The tag value is html decoded if dodecode is non-zero.
+ * The tag value may be NULL if there is no tag value..
+ */
+static void ap_ssi_get_tag_and_value(include_ctx_t *ctx, char **tag,
+                                     char **tag_val, int dodecode)
+{
+    if (!ctx->intern->argv) {
+        *tag = NULL;
+        *tag_val = NULL;
+
+        return;
+    }
 
-#define MAX_DEBUG_SIZE 10
-#define LOG_COND_STATUS(cntx, t_buck, h_ptr, ins_head, tag_text)
-#define DUMP_PARSE_EXPR_DEBUG(t_buck, h_ptr, d_buf, ins_head)
+    *tag_val = ctx->intern->argv->value;
+    *tag = ctx->intern->argv->name;
 
-#endif
-/*-------------------------------------------------------------------------*/
+    ctx->intern->argv = ctx->intern->argv->next;
 
-/* pjr - These seem to allow expr="fred" expr="joe" where joe overwrites fred. */
-static int handle_if(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                     request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                     apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    char *expr    = NULL;
-    int   expr_ret, was_error, was_unmatched;
-    apr_bucket *tmp_buck;
-    char debug_buf[MAX_DEBUG_SIZE];
-
-    *inserted_head = NULL;
-    if (!(ctx->flags & FLAG_PRINTING)) {
-        ctx->if_nesting_level++;
+    if (dodecode && *tag_val) {
+        decodehtml(*tag_val);
     }
-    else {
-        while (1) {
-            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 0);
-            if (tag == NULL) {
-                if (expr == NULL) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                  "missing expr in if statement: %s", 
-                                  r->filename);
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                    return 1;
-                }
-                expr_ret = parse_expr(r, ctx, expr, &was_error, 
-                                      &was_unmatched, debug_buf);
-                if (was_error) {
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                    return 1;
-                }
-                if (was_unmatched) {
-                    DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, 
-                                          "\nUnmatched '\n", *inserted_head);
-                }
-                DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, debug_buf, 
-                                      *inserted_head);
-                
-                if (expr_ret) {
-                    ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
-                }
-                else {
-                    ctx->flags &= FLAG_CLEAR_PRINT_COND;
-                }
-                LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, 
-                                "   if");
-                ctx->if_nesting_level = 0;
-                return 0;
-            }
-            else if (!strcmp(tag, "expr")) {
-                expr = tag_val;
-#ifdef DEBUG_INCLUDE
-                if (1) {
-                    apr_size_t d_len = 0;
-                    d_len = sprintf(debug_buf, "**** if expr=\"%s\"\n", expr);
-                    tmp_buck = apr_bucket_heap_create(debug_buf, d_len, NULL,
-                                                  r->connection->bucket_alloc);
-                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
 
-                    if (*inserted_head == NULL) {
-                        *inserted_head = tmp_buck;
-                    }
+    return;
+}
+
+static int find_file(request_rec *r, const char *directive, const char *tag,
+                     char *tag_val, apr_finfo_t *finfo)
+{
+    char *to_send = tag_val;
+    request_rec *rr = NULL;
+    int ret=0;
+    char *error_fmt = NULL;
+    apr_status_t rv = APR_SUCCESS;
+
+    if (!strcmp(tag, "file")) {
+        char *newpath;
+
+        /* be safe; only files in this directory or below allowed */
+        rv = apr_filepath_merge(&newpath, NULL, tag_val,
+                                APR_FILEPATH_NOTABOVEROOT |
+                                APR_FILEPATH_SECUREROOTTEST |
+                                APR_FILEPATH_NOTABSOLUTE, r->pool);
+
+        if (rv != APR_SUCCESS) {
+            error_fmt = "unable to access file \"%s\" "
+                        "in parsed file %s";
+        }
+        else {
+            /* note: it is okay to pass NULL for the "next filter" since
+               we never attempt to "run" this sub request. */
+            rr = ap_sub_req_lookup_file(newpath, r, NULL);
+
+            if (rr->status == HTTP_OK && rr->finfo.filetype != 0) {
+                to_send = rr->filename;
+                if ((rv = apr_stat(finfo, to_send,
+                    APR_FINFO_GPROT | APR_FINFO_MIN, rr->pool)) != APR_SUCCESS
+                    && rv != APR_INCOMPLETE) {
+                    error_fmt = "unable to get information about \"%s\" "
+                        "in parsed file %s";
                 }
-#endif
             }
             else {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "unknown parameter \"%s\" to tag if in %s", tag, 
-                            r->filename);
-                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
-                return 1;
+                error_fmt = "unable to lookup information about \"%s\" "
+                            "in parsed file %s";
             }
+        }
 
+        if (error_fmt) {
+            ret = -1;
+            ap_log_rerror(APLOG_MARK, APLOG_ERR,
+                          rv, r, error_fmt, to_send, r->filename);
         }
+
+        if (rr) ap_destroy_sub_req(rr);
+
+        return ret;
+    }
+    else if (!strcmp(tag, "virtual")) {
+        /* note: it is okay to pass NULL for the "next filter" since
+           we never attempt to "run" this sub request. */
+        rr = ap_sub_req_lookup_uri(tag_val, r, NULL);
+
+        if (rr->status == HTTP_OK && rr->finfo.filetype != 0) {
+            memcpy((char *) finfo, (const char *) &rr->finfo,
+                   sizeof(rr->finfo));
+            ap_destroy_sub_req(rr);
+            return 0;
+        }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unable to get "
+                          "information about \"%s\" in parsed file %s",
+                          tag_val, r->filename);
+            ap_destroy_sub_req(rr);
+            return -1;
+        }
+    }
+    else {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
+                      "to tag %s in %s", tag, directive, r->filename);
+        return -1;
     }
-    return 0;
 }
 
-static int handle_elif(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                       apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    char *expr    = NULL;
-    int   expr_ret, was_error, was_unmatched;
-    apr_bucket *tmp_buck;
-    char debug_buf[MAX_DEBUG_SIZE];
-
-    *inserted_head = NULL;
-    if (!ctx->if_nesting_level) {
-        while (1) {
-            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 0);
-            if (tag == '\0') {
-                LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, 
-                                " elif");
-                
-                if (ctx->flags & FLAG_COND_TRUE) {
-                    ctx->flags &= FLAG_CLEAR_PRINTING;
-                    return (0);
-                }
-                if (expr == NULL) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                  "missing expr in elif statement: %s", 
-                                  r->filename);
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                    return 1;
-                }
-                expr_ret = parse_expr(r, ctx, expr, &was_error, 
-                                      &was_unmatched, debug_buf);
-                if (was_error) {
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                    return 1;
-                }
-                if (was_unmatched) {
-                    DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, 
-                                          "\nUnmatched '\n", *inserted_head);
-                }
-                DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, debug_buf, 
-                                      *inserted_head);
-                
-                if (expr_ret) {
-                    ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
-                }
-                else {
-                    ctx->flags &= FLAG_CLEAR_PRINT_COND;
-                }
-                LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, 
-                                " elif");
-                return (0);
-            }
-            else if (!strcmp(tag, "expr")) {
-                expr = tag_val;
-#ifdef DEBUG_INCLUDE
-                if (1) {
-                    apr_size_t d_len = 0;
-                    d_len = sprintf(debug_buf, "**** elif expr=\"%s\"\n", expr);
-                    tmp_buck = apr_bucket_heap_create(debug_buf, d_len, NULL,
-                                                  r->connection->bucket_alloc);
-                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
+/*
+ * <!--#include virtual|file="..." [virtual|file="..."] ... -->
+ */
+static apr_status_t handle_include(include_ctx_t *ctx, ap_filter_t *f,
+                                   apr_bucket_brigade *bb)
+{
+    request_rec *r = f->r;
 
-                    if (*inserted_head == NULL) {
-                        *inserted_head = tmp_buck;
-                    }
-                }
-#endif
+    if (!ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "missing argument for include element in %s",
+                      r->filename);
+    }
+
+    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
+        return APR_SUCCESS;
+    }
+
+    if (!ctx->argc) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    while (1) {
+        char *tag     = NULL;
+        char *tag_val = NULL;
+        request_rec *rr = NULL;
+        char *error_fmt = NULL;
+        char *parsed_string;
+
+        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
+        if (!tag || !tag_val) {
+            break;
+        }
+
+        if (strcmp(tag, "virtual") && strcmp(tag, "file")) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
+                          "\"%s\" to tag include in %s", tag, r->filename);
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+            break;
+        }
+
+        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
+                                            SSI_EXPAND_DROP_NAME);
+        if (tag[0] == 'f') {
+            char *newpath;
+            apr_status_t rv;
+
+            /* be safe; only files in this directory or below allowed */
+            rv = apr_filepath_merge(&newpath, NULL, parsed_string,
+                                    APR_FILEPATH_NOTABOVEROOT |
+                                    APR_FILEPATH_SECUREROOTTEST |
+                                    APR_FILEPATH_NOTABSOLUTE, ctx->dpool);
+
+            if (rv != APR_SUCCESS) {
+                error_fmt = "unable to include file \"%s\" in parsed file %s";
             }
             else {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                               "unknown parameter \"%s\" to tag if in %s", tag, 
-                               r->filename);
-                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
-                return 1;
+                rr = ap_sub_req_lookup_file(newpath, r, f->next);
             }
         }
+        else {
+            rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
+        }
+
+        if (!error_fmt && rr->status != HTTP_OK) {
+            error_fmt = "unable to include \"%s\" in parsed file %s";
+        }
+
+        if (!error_fmt && (ctx->flags & SSI_FLAG_NO_EXEC) &&
+            rr->content_type && strncmp(rr->content_type, "text/", 5)) {
+
+            error_fmt = "unable to include potential exec \"%s\" in parsed "
+                        "file %s";
+        }
+
+        /* See the Kludge in includes_filter for why.
+         * Basically, it puts a bread crumb in here, then looks
+         * for the crumb later to see if its been here.
+         */
+        if (rr) {
+            ap_set_module_config(rr->request_config, &include_module, r);
+        }
+
+        if (!error_fmt && ap_run_sub_req(rr)) {
+            error_fmt = "unable to include \"%s\" in parsed file %s";
+        }
+
+        if (error_fmt) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error_fmt, tag_val,
+                          r->filename);
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        }
+
+        /* Do *not* destroy the subrequest here; it may have allocated
+         * variables in this r->subprocess_env in the subrequest's
+         * r->pool, so that pool must survive as long as this request.
+         * Yes, this is a memory leak. */
+
+        if (error_fmt) {
+            break;
+        }
     }
-    return 0;
+
+    return APR_SUCCESS;
 }
 
-static int handle_else(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                       apr_bucket **inserted_head)
+/*
+ * <!--#echo [encoding="..."] var="..." [encoding="..."] var="..." ... -->
+ */
+static apr_status_t handle_echo(include_ctx_t *ctx, ap_filter_t *f,
+                                apr_bucket_brigade *bb)
 {
-    char *tag = NULL;
-    char *tag_val = NULL;
-    apr_bucket *tmp_buck;
+    enum {E_NONE, E_URL, E_ENTITY} encode;
+    request_rec *r = f->r;
 
-    *inserted_head = NULL;
-    if (!ctx->if_nesting_level) {
-        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
-        if ((tag != NULL) || (tag_val != NULL)) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                        "else directive does not take tags in %s", r->filename);
-            if (ctx->flags & FLAG_PRINTING) {
-                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
+    if (!ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "missing argument for echo element in %s",
+                      r->filename);
+    }
+
+    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
+        return APR_SUCCESS;
+    }
+
+    if (!ctx->argc) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    encode = E_ENTITY;
+
+    while (1) {
+        char *tag = NULL;
+        char *tag_val = NULL;
+
+        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
+        if (!tag || !tag_val) {
+            break;
+        }
+
+        if (!strcmp(tag, "var")) {
+            const char *val;
+            const char *echo_text = NULL;
+            apr_size_t e_len;
+
+            val = get_include_var(ap_ssi_parse_string(ctx, tag_val, NULL,
+                                                      0, SSI_EXPAND_DROP_NAME),
+                                  ctx);
+
+            if (val) {
+                switch(encode) {
+                case E_NONE:
+                    echo_text = val;
+                    break;
+                case E_URL:
+                    echo_text = ap_escape_uri(ctx->dpool, val);
+                    break;
+                case E_ENTITY:
+                    echo_text = ap_escape_html(ctx->dpool, val);
+                    break;
+                }
+
+                e_len = strlen(echo_text);
             }
-            return -1;
+            else {
+                echo_text = ctx->intern->undefined_echo;
+                e_len = ctx->intern->undefined_echo_len;
+            }
+
+            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(
+                                    apr_pmemdup(ctx->pool, echo_text, e_len),
+                                    e_len, ctx->pool, f->c->bucket_alloc));
         }
-        else {
-            LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, " else");
-            
-            if (ctx->flags & FLAG_COND_TRUE) {
-                ctx->flags &= FLAG_CLEAR_PRINTING;
+        else if (!strcmp(tag, "encoding")) {
+            if (!strcasecmp(tag_val, "none")) {
+                encode = E_NONE;
+            }
+            else if (!strcasecmp(tag_val, "url")) {
+                encode = E_URL;
+            }
+            else if (!strcasecmp(tag_val, "entity")) {
+                encode = E_ENTITY;
             }
             else {
-                ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown value "
+                              "\"%s\" to parameter \"encoding\" of tag echo in "
+                              "%s", tag_val, r->filename);
+                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+                break;
             }
-            return 0;
+        }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
+                          "\"%s\" in tag echo of %s", tag, r->filename);
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+            break;
         }
     }
-    return 0;
+
+    return APR_SUCCESS;
 }
 
-static int handle_endif(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                        request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                        apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    apr_bucket *tmp_buck;
-
-    *inserted_head = NULL;
-    if (!ctx->if_nesting_level) {
-        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
-        if ((tag != NULL) || (tag_val != NULL)) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                       "endif directive does not take tags in %s", r->filename);
-            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
-            return -1;
-        }
-        else {
-            LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, "endif");
-            ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
-            return 0;
-        }
+/*
+ * <!--#config [timefmt="..."] [sizefmt="..."] [errmsg="..."]
+ *             [echomsg="..."] -->
+ */
+static apr_status_t handle_config(include_ctx_t *ctx, ap_filter_t *f,
+                                  apr_bucket_brigade *bb)
+{
+    request_rec *r = f->r;
+    apr_table_t *env = r->subprocess_env;
+
+    if (!ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "missing argument for config element in %s",
+                      r->filename);
     }
-    else {
-        ctx->if_nesting_level--;
-        return 0;
+
+    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
+        return APR_SUCCESS;
     }
-}
 
-static int handle_set(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                      request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
-                      apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    char *var     = NULL;
-    apr_bucket *tmp_buck;
-    char *parsed_string;
-    request_rec *sub = r->main;
-    apr_pool_t *p = r->pool;
+    if (!ctx->argc) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    while (1) {
+        char *tag     = NULL;
+        char *tag_val = NULL;
+
+        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_RAW);
+        if (!tag || !tag_val) {
+            break;
+        }
+
+        if (!strcmp(tag, "errmsg")) {
+            ctx->error_str = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
+                                                 SSI_EXPAND_DROP_NAME);
+        }
+        else if (!strcmp(tag, "echomsg")) {
+            ctx->intern->undefined_echo =
+                ap_ssi_parse_string(ctx, tag_val, NULL, 0,SSI_EXPAND_DROP_NAME);
+            ctx->intern->undefined_echo_len=strlen(ctx->intern->undefined_echo);
+        }
+        else if (!strcmp(tag, "timefmt")) {
+            apr_time_t date = r->request_time;
+
+            ctx->time_str = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
+                                                SSI_EXPAND_DROP_NAME);
+
+            apr_table_setn(env, "DATE_LOCAL", ap_ht_time(r->pool, date,
+                           ctx->time_str, 0));
+            apr_table_setn(env, "DATE_GMT", ap_ht_time(r->pool, date,
+                           ctx->time_str, 1));
+            apr_table_setn(env, "LAST_MODIFIED",
+                           ap_ht_time(r->pool, r->finfo.mtime,
+                           ctx->time_str, 0));
+        }
+        else if (!strcmp(tag, "sizefmt")) {
+            char *parsed_string;
+
+            parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
+                                                SSI_EXPAND_DROP_NAME);
+            if (!strcmp(parsed_string, "bytes")) {
+                ctx->flags |= SSI_FLAG_SIZE_IN_BYTES;
+            }
+            else if (!strcmp(parsed_string, "abbrev")) {
+                ctx->flags &= SSI_FLAG_SIZE_ABBREV;
+            }
+            else {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown value "
+                              "\"%s\" to parameter \"sizefmt\" of tag config "
+                              "in %s", parsed_string, r->filename);
+                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+                break;
+            }
+        }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
+                          "\"%s\" to tag config in %s", tag, r->filename);
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+            break;
+        }
+    }
+
+    return APR_SUCCESS;
+}
+
+/*
+ * <!--#fsize virtual|file="..." [virtual|file="..."] ... -->
+ */
+static apr_status_t handle_fsize(include_ctx_t *ctx, ap_filter_t *f,
+                                 apr_bucket_brigade *bb)
+{
+    request_rec *r = f->r;
+
+    if (!ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "missing argument for fsize element in %s",
+                      r->filename);
+    }
+
+    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
+        return APR_SUCCESS;
+    }
+
+    if (!ctx->argc) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    while (1) {
+        char *tag     = NULL;
+        char *tag_val = NULL;
+        apr_finfo_t finfo;
+        char *parsed_string;
+
+        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
+        if (!tag || !tag_val) {
+            break;
+        }
+
+        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
+                                            SSI_EXPAND_DROP_NAME);
+
+        if (!find_file(r, "fsize", tag, parsed_string, &finfo)) {
+            char *buf;
+            apr_size_t len;
+
+            if (!(ctx->flags & SSI_FLAG_SIZE_IN_BYTES)) {
+                buf = apr_strfsize(finfo.size, apr_palloc(ctx->pool, 5));
+                len = 4; /* omit the \0 terminator */
+            }
+            else {
+                apr_size_t l, x, pos;
+                char *tmp;
+
+                tmp = apr_psprintf(ctx->dpool, "%" APR_OFF_T_FMT, finfo.size);
+                len = l = strlen(tmp);
+
+                for (x = 0; x < l; ++x) {
+                    if (x && !((l - x) % 3)) {
+                        ++len;
+                    }
+                }
+
+                if (len == l) {
+                    buf = apr_pstrmemdup(ctx->pool, tmp, len);
+                }
+                else {
+                    buf = apr_palloc(ctx->pool, len);
+
+                    for (pos = x = 0; x < l; ++x) {
+                        if (x && !((l - x) % 3)) {
+                            buf[pos++] = ',';
+                        }
+                        buf[pos++] = tmp[x];
+                    }
+                }
+            }
+
+            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(buf, len,
+                                    ctx->pool, f->c->bucket_alloc));
+        }
+        else {
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+            break;
+        }
+    }
+
+    return APR_SUCCESS;
+}
+
+/*
+ * <!--#flastmod virtual|file="..." [virtual|file="..."] ... -->
+ */
+static apr_status_t handle_flastmod(include_ctx_t *ctx, ap_filter_t *f,
+                                    apr_bucket_brigade *bb)
+{
+    request_rec *r = f->r;
+
+    if (!ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "missing argument for flastmod element in %s",
+                      r->filename);
+    }
+
+    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
+        return APR_SUCCESS;
+    }
+
+    if (!ctx->argc) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    while (1) {
+        char *tag     = NULL;
+        char *tag_val = NULL;
+        apr_finfo_t  finfo;
+        char *parsed_string;
+
+        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
+        if (!tag || !tag_val) {
+            break;
+        }
+
+        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
+                                            SSI_EXPAND_DROP_NAME);
+
+        if (!find_file(r, "flastmod", tag, parsed_string, &finfo)) {
+            char *t_val;
+            apr_size_t t_len;
+
+            t_val = ap_ht_time(ctx->pool, finfo.mtime, ctx->time_str, 0);
+            t_len = strlen(t_val);
+
+            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(t_val, t_len,
+                                    ctx->pool, f->c->bucket_alloc));
+        }
+        else {
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+            break;
+        }
+    }
+
+    return APR_SUCCESS;
+}
+
+/*
+ * <!--#if expr="..." -->
+ */
+static apr_status_t handle_if(include_ctx_t *ctx, ap_filter_t *f,
+                              apr_bucket_brigade *bb)
+{
+    char *tag = NULL;
+    char *expr = NULL;
+    request_rec *r = f->r;
+    int expr_ret, was_error;
+
+    if (ctx->argc != 1) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, (ctx->argc)
+                                ? "too many arguments for if element in %s"
+                                : "missing expr argument for if element in %s",
+                      r->filename);
+    }
+
+    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
+        ++(ctx->if_nesting_level);
+        return APR_SUCCESS;
+    }
+
+    if (ctx->argc != 1) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    ap_ssi_get_tag_and_value(ctx, &tag, &expr, SSI_VALUE_RAW);
+
+    if (strcmp(tag, "expr")) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
+                      "to tag if in %s", tag, r->filename);
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    if (!expr) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "missing expr value for if "
+                      "element in %s", r->filename);
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    DEBUG_PRINTF((ctx, "****    if expr=\"%s\"\n", expr));
+
+    expr_ret = parse_expr(ctx, expr, &was_error);
+
+    if (was_error) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    if (expr_ret) {
+        ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);
+    }
+    else {
+        ctx->flags &= SSI_FLAG_CLEAR_PRINT_COND;
+    }
+
+    DEBUG_DUMP_COND(ctx, "   if");
+
+    ctx->if_nesting_level = 0;
+
+    return APR_SUCCESS;
+}
+
+/*
+ * <!--#elif expr="..." -->
+ */
+static apr_status_t handle_elif(include_ctx_t *ctx, ap_filter_t *f,
+                                apr_bucket_brigade *bb)
+{
+    char *tag = NULL;
+    char *expr = NULL;
+    request_rec *r = f->r;
+    int expr_ret, was_error;
+
+    if (ctx->argc != 1) {
+        ap_log_rerror(APLOG_MARK,
+                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
+                      0, r, (ctx->argc)
+                                ? "too many arguments for if element in %s"
+                                : "missing expr argument for if element in %s",
+                      r->filename);
+    }
+
+    if (ctx->if_nesting_level) {
+        return APR_SUCCESS;
+    }
+
+    if (ctx->argc != 1) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    ap_ssi_get_tag_and_value(ctx, &tag, &expr, SSI_VALUE_RAW);
+
+    if (strcmp(tag, "expr")) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
+                      "to tag if in %s", tag, r->filename);
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    if (!expr) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "missing expr in elif "
+                      "statement: %s", r->filename);
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    DEBUG_PRINTF((ctx, "****  elif expr=\"%s\"\n", expr));
+    DEBUG_DUMP_COND(ctx, " elif");
+
+    if (ctx->flags & SSI_FLAG_COND_TRUE) {
+        ctx->flags &= SSI_FLAG_CLEAR_PRINTING;
+        return APR_SUCCESS;
+    }
+
+    expr_ret = parse_expr(ctx, expr, &was_error);
+
+    if (was_error) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    if (expr_ret) {
+        ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);
+    }
+    else {
+        ctx->flags &= SSI_FLAG_CLEAR_PRINT_COND;
+    }
+
+    DEBUG_DUMP_COND(ctx, " elif");
+
+    return APR_SUCCESS;
+}
+
+/*
+ * <!--#else -->
+ */
+static apr_status_t handle_else(include_ctx_t *ctx, ap_filter_t *f,
+                                apr_bucket_brigade *bb)
+{
+    request_rec *r = f->r;
+
+    if (ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "else directive does not take tags in %s",
+                      r->filename);
+    }
+
+    if (ctx->if_nesting_level) {
+        return APR_SUCCESS;
+    }
+
+    if (ctx->argc) {
+        if (ctx->flags & SSI_FLAG_PRINTING) {
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        }
+
+        return APR_SUCCESS;
+    }
+
+    DEBUG_DUMP_COND(ctx, " else");
+
+    if (ctx->flags & SSI_FLAG_COND_TRUE) {
+        ctx->flags &= SSI_FLAG_CLEAR_PRINTING;
+    }
+    else {
+        ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);
+    }
+
+    return APR_SUCCESS;
+}
+
+/*
+ * <!--#endif -->
+ */
+static apr_status_t handle_endif(include_ctx_t *ctx, ap_filter_t *f,
+                                 apr_bucket_brigade *bb)
+{
+    request_rec *r = f->r;
+
+    if (ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "endif directive does not take tags in %s",
+                      r->filename);
+    }
+
+    if (ctx->if_nesting_level) {
+        --(ctx->if_nesting_level);
+        return APR_SUCCESS;
+    }
+
+    if (ctx->argc) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    DEBUG_DUMP_COND(ctx, "endif");
+
+    ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);
+
+    return APR_SUCCESS;
+}
+
+/*
+ * <!--#set var="..." value="..." ... -->
+ */
+static apr_status_t handle_set(include_ctx_t *ctx, ap_filter_t *f,
+                               apr_bucket_brigade *bb)
+{
+    char *var = NULL;
+    request_rec *r = f->r;
+    request_rec *sub = r->main;
+    apr_pool_t *p = r->pool;
+
+    if (ctx->argc < 2) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "missing argument for set element in %s",
+                      r->filename);
+    }
+
+    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
+        return APR_SUCCESS;
+    }
+
+    if (ctx->argc < 2) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    /* we need to use the 'main' request pool to set notes as that is
+     * a notes lifetime
+     */
+    while (sub) {
+        p = sub->pool;
+        sub = sub->main;
+    }
+
+    while (1) {
+        char *tag = NULL;
+        char *tag_val = NULL;
+
+        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
+
+        if (!tag || !tag_val) {
+            break;
+        }
+
+        if (!strcmp(tag, "var")) {
+            var = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
+                                      SSI_EXPAND_DROP_NAME);
+        }
+        else if (!strcmp(tag, "value")) {
+            char *parsed_string;
+
+            if (!var) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "variable must "
+                              "precede value in set directive in %s",
+                              r->filename);
+                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+                break;
+            }
+
+            parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
+                                                SSI_EXPAND_DROP_NAME);
+            apr_table_setn(r->subprocess_env, apr_pstrdup(p, var),
+                           apr_pstrdup(p, parsed_string));
+        }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Invalid tag for set "
+                          "directive in %s", r->filename);
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+            break;
+        }
+    }
+
+    return APR_SUCCESS;
+}
+
+/*
+ * <!--#printenv -->
+ */
+static apr_status_t handle_printenv(include_ctx_t *ctx, ap_filter_t *f,
+                                    apr_bucket_brigade *bb)
+{
+    request_rec *r = f->r;
+    const apr_array_header_t *arr;
+    const apr_table_entry_t *elts;
+    int i;
+
+    if (ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "printenv directive does not take tags in %s",
+                      r->filename);
+    }
+
+    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
+        return APR_SUCCESS;
+    }
+
+    if (ctx->argc) {
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    arr = apr_table_elts(r->subprocess_env);
+    elts = (apr_table_entry_t *)arr->elts;
+
+    for (i = 0; i < arr->nelts; ++i) {
+        const char *key_text, *val_text;
+        char *key_val, *next;
+        apr_size_t k_len, v_len, kv_length;
+
+        /* get key */
+        key_text = ap_escape_html(ctx->dpool, elts[i].key);
+        k_len = strlen(key_text);
+
+        /* get value */
+        val_text = elts[i].val;
+        if (val_text == LAZY_VALUE) {
+            val_text = add_include_vars_lazy(r, elts[i].key);
+        }
+        val_text = ap_escape_html(ctx->dpool, elts[i].val);
+        v_len = strlen(val_text);
+
+        /* assemble result */
+        kv_length = k_len + v_len + sizeof("=\n");
+        key_val = apr_palloc(ctx->pool, kv_length);
+        next = key_val;
+
+        memcpy(next, key_text, k_len);
+        next += k_len;
+        *next++ = '=';
+        memcpy(next, val_text, v_len);
+        next += v_len;
+        *next++ = '\n';
+        *next = 0;
+
+        APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(key_val, kv_length-1,
+                                ctx->pool, f->c->bucket_alloc));
+    }
+
+    ctx->flush_now = 1;
+    return APR_SUCCESS;
+}
+
+
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |               Main Includes-Filter Engine
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+/* This is an implementation of the BNDM search algorithm.
+ *
+ * Fast and Flexible String Matching by Combining Bit-parallelism and
+ * Suffix Automata (2001)
+ * Gonzalo Navarro, Mathieu Raffinot
+ *
+ * http://www-igm.univ-mlv.fr/~raffinot/ftp/jea2001.ps.gz
+ *
+ * Initial code submitted by Sascha Schumann.
+ */
+
+/* Precompile the bndm_t data structure. */
+static bndm_t *bndm_compile(apr_pool_t *pool, const char *n, apr_size_t nl)
+{
+    unsigned int x;
+    const char *ne = n + nl;
+    bndm_t *t = apr_palloc(pool, sizeof(*t));
+
+    memset(t->T, 0, sizeof(unsigned int) * 256);
+    t->pattern_len = nl;
+
+    for (x = 1; n < ne; x <<= 1) {
+        t->T[(unsigned char) *n++] |= x;
+    }
+
+    t->x = x - 1;
+
+    return t;
+}
+
+/* Implements the BNDM search algorithm (as described above).
+ *
+ * h  - the string to look in
+ * hl - length of the string to look for
+ * t  - precompiled bndm structure against the pattern
+ *
+ * Returns the count of character that is the first match or hl if no
+ * match is found.
+ */
+static apr_size_t bndm(bndm_t *t, const char *h, apr_size_t hl)
+{
+    const char *skip;
+    const char *he, *p, *pi;
+    unsigned int *T, x, d;
+    apr_size_t nl;
+
+    he = h + hl;
+
+    T = t->T;
+    x = t->x;
+    nl = t->pattern_len;
 
-    /* we need to use the 'main' request pool to set notes as that is 
-     * a notes lifetime
-     */
-    while (sub) {
-        p = sub->pool;
-        sub = sub->main;
-    }
+    pi = h - 1; /* pi: p initial */
+    p = pi + nl; /* compare window right to left. point to the first char */
 
-    *inserted_head = NULL;
-    if (ctx->flags & FLAG_PRINTING) {
-        while (1) {
-            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
-            if ((tag == NULL) && (tag_val == NULL)) {
-                return 0;
-            }
-            else if (tag_val == NULL) {
-                return 1;
-            }
-            else if (!strcmp(tag, "var")) {
-                var = ap_ssi_parse_string(r, ctx, tag_val, NULL,
-                                          MAX_STRING_LEN, 0);
-            }
-            else if (!strcmp(tag, "value")) {
-                if (var == (char *) NULL) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                           "variable must precede value in set directive in %s",
-                           r->filename);
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
-                                        *inserted_head);
-                    return (-1);
-                }
-                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
-                                                    MAX_STRING_LEN, 0);
-                apr_table_setn(r->subprocess_env, apr_pstrdup(p, var),
-                               apr_pstrdup(p, parsed_string));
-            }
-            else {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                            "Invalid tag for set directive in %s", r->filename);
-                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
-                return -1;
+    while (p < he) {
+        skip = p;
+        d = x;
+        do {
+            d &= T[(unsigned char) *p--];
+            if (!d) {
+                break;
             }
-        }
-    }
-    return 0;
-}
-
-static int handle_printenv(include_ctx_t *ctx, apr_bucket_brigade **bb, 
-                           request_rec *r, ap_filter_t *f, 
-                           apr_bucket *head_ptr, apr_bucket **inserted_head)
-{
-    char *tag     = NULL;
-    char *tag_val = NULL;
-    apr_bucket *tmp_buck;
-
-    if (ctx->flags & FLAG_PRINTING) {
-        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
-        if ((tag == NULL) && (tag_val == NULL)) {
-            const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
-            const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
-            int i;
-            const char *key_text, *val_text;
-            char *key_val, *next;
-            apr_size_t   k_len, v_len, kv_length;
-
-            *inserted_head = NULL;
-            for (i = 0; i < arr->nelts; ++i) {
-                key_text = ap_escape_html(r->pool, elts[i].key);
-                val_text = elts[i].val;
-                if (val_text == LAZY_VALUE) {
-                    val_text = add_include_vars_lazy(r, elts[i].key, ctx->time_str);
-                }
-                val_text = ap_escape_html(r->pool, elts[i].val);
-                k_len = strlen(key_text);
-                v_len = strlen(val_text);
-                kv_length = k_len + v_len + sizeof("=\n");
-                key_val = apr_palloc(r->pool, kv_length);
-                next = key_val;
-                memcpy(next, key_text, k_len);
-                next += k_len;
-                *next++ = '=';
-                memcpy(next, val_text, v_len);
-                next += v_len;
-                *next++ = '\n';
-                *next = 0;
-                tmp_buck = apr_bucket_pool_create(key_val, kv_length - 1,
-                                                  r->pool,
-                                                  r->connection->bucket_alloc);
-                APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
-                if (*inserted_head == NULL) {
-                    *inserted_head = tmp_buck;
+            if ((d & 1)) {
+                if (p != pi) {
+                    skip = p;
+                }
+                else {
+                    return p - h + 1;
                 }
             }
-            return 0;
-        }
-        else {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                        "printenv directive does not take tags in %s", 
-                        r->filename);
-            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
-            return -1;
-        }
+            d >>= 1;
+        } while (d);
+
+        pi = skip;
+        p = pi + nl;
     }
-    return 0;
-}
 
-/* -------------------------- The main function --------------------------- */
+    return hl;
+}
 
 /*
  * returns the index position of the first byte of start_seq (or the len of
  * the buffer as non-match)
  */
-static apr_size_t find_start_sequence(ssi_ctx_t *ctx, const char *data,
+static apr_size_t find_start_sequence(include_ctx_t *ctx, const char *data,
                                       apr_size_t len)
 {
-    apr_size_t slen = ctx->ctx->start_seq_len;
+    struct ssi_internal_ctx *intern = ctx->intern;
+    apr_size_t slen = intern->start_seq_pat->pattern_len;
     apr_size_t index;
     const char *p, *ep;
 
     if (len < slen) {
         p = data; /* try partial match at the end of the buffer (below) */
     }
     else {
         /* try fast bndm search over the buffer
          * (hopefully the whole start sequence can be found in this buffer)
          */
-        index = bndm(ctx->ctx->start_seq, ctx->ctx->start_seq_len, data, len,
-                     ctx->ctx->start_seq_pat);
+        index = bndm(intern->start_seq_pat, data, len);
 
         /* wow, found it. ready. */
         if (index < len) {
-            ctx->state = PARSE_DIRECTIVE;
+            intern->state = PARSE_DIRECTIVE;
             return index;
         }
         else {
             /* ok, the pattern can't be found as whole in the buffer,
              * check the end for a partial match
              */
             p = data + len - slen + 1;
         }
     }
 
     ep = data + len;
     do {
-        while (p < ep && *p != *ctx->ctx->start_seq) {
+        while (p < ep && *p != *intern->start_seq) {
             ++p;
         }
 
         index = p - data;
 
         /* found a possible start_seq start */
         if (p < ep) {
             apr_size_t pos = 1;
 
             ++p;
-            while (p < ep && *p == ctx->ctx->start_seq[pos]) {
+            while (p < ep && *p == intern->start_seq[pos]) {
                 ++p;
                 ++pos;
             }
 
             /* partial match found. Store the info for the next round */
             if (p == ep) {
-                ctx->state = PARSE_HEAD;
-                ctx->ctx->parse_pos = pos;
+                intern->state = PARSE_HEAD;
+                intern->parse_pos = pos;
                 return index;
             }
         }
 
         /* we must try all combinations; consider (e.g.) SSIStartTag "--->"
          * and a string data of "--.-" and the end of the buffer

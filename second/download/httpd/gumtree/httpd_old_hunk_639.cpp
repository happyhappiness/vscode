        }
    }

    *p = '\0';
}

/*
 * Extract the next tag name and value.
 * If there are no more tags, set the tag name to NULL.
 * The tag value is html decoded if dodecode is non-zero.
 * The tag value may be NULL if there is no tag value..
 *    format:
 *        [WS]<Tag>[WS]=[WS]['|"|`]<Value>[['|"|`|]|WS]
 */

#define SKIP_TAG_WHITESPACE(ptr) while ((*ptr != '\0') && (apr_isspace (*ptr))) ptr++

static void ap_ssi_get_tag_and_value(include_ctx_t *ctx, char **tag,
                                     char **tag_val, int dodecode)
{
    *tag_val = NULL;
    if (ctx->curr_tag_pos >= ctx->combined_tag + ctx->tag_length) {
        *tag = NULL;
        return;
    }

    *tag = ctx->curr_tag_pos;
    if (!**tag) {
        *tag = NULL;
        /* finitio */
        ctx->curr_tag_pos = ctx->combined_tag + ctx->tag_length;
        return;
    }

    *tag_val = ap_strchr(*tag, '=');
    if (!*tag_val) {
        ctx->curr_tag_pos = ctx->combined_tag + ctx->tag_length;
        return;
    }

    /* if it starts with '=' there was no tag name, just a value */
    if (*tag_val == *tag) {
        *tag = NULL;
    }

    *(*tag_val)++ = '\0';
    ctx->curr_tag_pos = *tag_val + strlen(*tag_val) + 1; /* skip \0 byte */

    if (dodecode) {
        decodehtml(*tag_val);
    }

    return;
}

/* initial buffer size for power-of-two allocator in ap_ssi_parse_string */
#define PARSE_STRING_INITIAL_SIZE 64

/*
 * Do variable substitution on strings
 * (Note: If out==NULL, this function allocs a buffer for the resulting
 * string from r->pool.  The return value is the parsed string)
 */
static char *ap_ssi_parse_string(request_rec *r, include_ctx_t *ctx, 
                                 const char *in, char *out,
                                 apr_size_t length, int leave_name)
{
    char ch;
    char *next;
    char *end_out;
    apr_size_t out_size;

    /* allocate an output buffer if needed */
    if (!out) {
        out_size = PARSE_STRING_INITIAL_SIZE;
        if (out_size > length) {
            out_size = length;
        }
        out = apr_palloc(r->pool, out_size);
    }
    else {
        out_size = length;
    }

    /* leave room for nul terminator */
    end_out = out + out_size - 1;

    next = out;
    while ((ch = *in++) != '\0') {
        switch (ch) {
        case '\\':
            if (next == end_out) {
                if (out_size < length) {
                    /* double the buffer size */
                    apr_size_t new_out_size = out_size * 2;
                    apr_size_t current_length = next - out;
                    char *new_out;
                    if (new_out_size > length) {
                        new_out_size = length;
                    }
                    new_out = apr_palloc(r->pool, new_out_size);
                    memcpy(new_out, out, current_length);
                    out = new_out;
                    out_size = new_out_size;
                    end_out = out + out_size - 1;
                    next = out + current_length;
                }
                else {
                    /* truncated */
                    *next = '\0';
                    return out;
                }
            }
            if (*in == '$') {
                *next++ = *in++;
            }
            else {
                *next++ = ch;
            }
            break;
        case '$':
            {
                const char *start_of_var_name;
                char *end_of_var_name;        /* end of var name + 1 */
                const char *expansion, *temp_end, *val;
                char        tmp_store;
                apr_size_t l;

                /* guess that the expansion won't happen */
                expansion = in - 1;
                if (*in == '{') {
                    ++in;
                    start_of_var_name = in;
                    in = ap_strchr_c(in, '}');
                    if (in == NULL) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                                      0, r, "Missing '}' on variable \"%s\"",
                                      expansion);
                        *next = '\0';
                        return out;
                    }
                    temp_end = in;
                    end_of_var_name = (char *)temp_end;
                    ++in;
                }
                else {
                    start_of_var_name = in;
                    while (apr_isalnum(*in) || *in == '_') {
                        ++in;
                    }
                    temp_end = in;
                    end_of_var_name = (char *)temp_end;
                }
                /* what a pain, too bad there's no table_getn where you can
                 * pass a non-nul terminated string */
                l = end_of_var_name - start_of_var_name;
                if (l != 0) {
                    tmp_store        = *end_of_var_name;
                    *end_of_var_name = '\0';
                    val = get_include_var(r, ctx, start_of_var_name);
                    *end_of_var_name = tmp_store;

                    if (val) {
                        expansion = val;
                        l = strlen(expansion);
                    }
                    else if (leave_name) {
                        l = in - expansion;
                    }
                    else {
                        /* no expansion to be done */
                        break;
                    }
                }
                else {
                    /* zero-length variable name causes just the $ to be 
                     * copied */
                    l = 1;
                }
                if ((next + l > end_out) && (out_size < length)) {
                    /* increase the buffer size to accommodate l more chars */
                    apr_size_t new_out_size = out_size;
                    apr_size_t current_length = next - out;
                    char *new_out;
                    do {
                        new_out_size *= 2;
                    } while (new_out_size < current_length + l + 1); /* +1 for NUL */
                    if (new_out_size > length) {
                        new_out_size = length;
                    }
                    new_out = apr_palloc(r->pool, new_out_size);
                    memcpy(new_out, out, current_length);
                    out = new_out;
                    out_size = new_out_size;
                    end_out = out + out_size - 1;
                    next = out + current_length;
                }
                l = ((int)l > end_out - next) ? (end_out - next) : l;
                memcpy(next, expansion, l);
                next += l;
                break;
            }
        default:
            if (next == end_out) {
                if (out_size < length) {
                    /* double the buffer size */
                    apr_size_t new_out_size = out_size * 2;
                    apr_size_t current_length = next - out;
                    char *new_out;
                    if (new_out_size > length) {
                        new_out_size = length;
                    }
                    new_out = apr_palloc(r->pool, new_out_size);
                    memcpy(new_out, out, current_length);
                    out = new_out;
                    out_size = new_out_size;
                    end_out = out + out_size - 1;
                    next = out + current_length;
                }
                else {
                    /* truncated */
                    *next = '\0';
                    return out;
                }
            }
            *next++ = ch;
            break;
        }
    }
    *next = '\0';
    return out;
}

/* --------------------------- Action handlers ---------------------------- */

/* ensure that path is relative, and does not contain ".." elements
 * ensentially ensure that it does not match the regex:
 * (^/|(^|/)\.\.(/|$))
 * XXX: Simply replace with apr_filepath_merge                    
 */
static int is_only_below(const char *path)
{
#ifdef HAVE_DRIVE_LETTERS
    if (path[1] == ':') 
        return 0;
#endif
#ifdef NETWARE
    if (ap_strchr_c(path, ':'))
        return 0;
#endif
    if (path[0] == '/') {
        return 0;
    }
    while (*path) {
        int dots = 0;
        while (path[dots] == '.')
            ++dots;
#if defined(WIN32) 
        /* If the name is canonical this is redundant
         * but in security, redundancy is worthwhile.
         * Does OS2 belong here (accepts ... for ..)?
         */
        if (dots > 1 && (!path[dots] || path[dots] == '/'))
            return 0;
#else
        if (dots == 2 && (!path[dots] || path[dots] == '/'))
            return 0;
#endif
        path += dots;
        /* Advance to either the null byte at the end of the
         * string or the character right after the next slash,
         * whichever comes first
         */
        while (*path && (*path++ != '/')) {
            continue;
        }
    }
    return 1;
}

static int handle_include(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                         request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                         apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    apr_bucket  *tmp_buck;
    char *parsed_string;
    int loglevel = APLOG_ERR;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
            if (tag_val == NULL) {
                if (tag == NULL) {
                    return (0);
                }
                else {
                    return (1);
                }
            }
            if (!strcmp(tag, "virtual") || !strcmp(tag, "file")) {
                request_rec *rr = NULL;
                char *error_fmt = NULL;
                apr_status_t rc = APR_SUCCESS;

                SPLIT_AND_PASS_PRETAG_BUCKETS(*bb, ctx, f->next, rc);
                if (rc != APR_SUCCESS) {
                    return rc;
                }
 
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                if (tag[0] == 'f') {
                    /* XXX: Port to apr_filepath_merge
                     * be safe; only files in this directory or below allowed 
                     */
                    if (!is_only_below(parsed_string)) {
                        error_fmt = "unable to include file \"%s\" "
                                    "in parsed file %s";
                    }
                    else {
                        rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
                    }
                }
                else {
                    rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
                }

                if (!error_fmt && rr->status != HTTP_OK) {
                    error_fmt = "unable to include \"%s\" in parsed file %s";
                }

                if (!error_fmt && (ctx->flags & FLAG_NO_EXEC) && 
                    rr->content_type && 
                    (strncmp(rr->content_type, "text/", 5))) {
                    error_fmt = "unable to include potential exec \"%s\" "
                        "in parsed file %s";
                }

                /* See the Kludge in send_parsed_file for why */
                /* Basically, it puts a bread crumb in here, then looks */
                /*   for the crumb later to see if its been here.       */
                if (rr) 
                    ap_set_module_config(rr->request_config, 
                                         &include_module, r);

                if (!error_fmt && ap_run_sub_req(rr)) {
                    error_fmt = "unable to include \"%s\" in parsed file %s";
                }
                if (error_fmt) {
                    ap_log_rerror(APLOG_MARK, loglevel,
                                  0, r, error_fmt, tag_val, r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                }
                
                /* Do *not* destroy the subrequest here; it may have allocated
                 * variables in this r->subprocess_env in the subrequest's
                 * r->pool, so that pool must survive as long as this request.
                 * Yes, this is a memory leak. */
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" to tag include in %s",
                            tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }
        }
    }
    return 0;
}


static int handle_echo(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                       apr_bucket **inserted_head)
{
    char       *tag       = NULL;
    char       *tag_val   = NULL;
    const char *echo_text = NULL;
    apr_bucket  *tmp_buck;
    apr_size_t e_len;
    enum {E_NONE, E_URL, E_ENTITY} encode;

    encode = E_ENTITY;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
            if (tag_val == NULL) {
                if (tag != NULL) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            if (!strcmp(tag, "var")) {
                conn_rec *c = r->connection;
                const char *val =
                    get_include_var(r, ctx,
                                    ap_ssi_parse_string(r, ctx, tag_val, NULL,
                                                        MAX_STRING_LEN, 0));
                if (val) {
                    switch(encode) {
                    case E_NONE:   
                        echo_text = val;
                        break;
                    case E_URL:
                        echo_text = ap_escape_uri(r->pool, val);  
                        break;
                    case E_ENTITY: 
                        echo_text = ap_escape_html(r->pool, val); 
                        break;
                    }

                    e_len = strlen(echo_text);
                    tmp_buck = apr_bucket_pool_create(echo_text, e_len,
                                                      r->pool, c->bucket_alloc);
                }
                else {
                    include_server_config *sconf= 
                        ap_get_module_config(r->server->module_config,
                                             &include_module);
                    tmp_buck = apr_bucket_pool_create(sconf->undefinedEcho, 
                                                      sconf->undefinedEchoLen,
                                                      r->pool, c->bucket_alloc);
                }
                APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
                if (*inserted_head == NULL) {
                    *inserted_head = tmp_buck;
                }
            }
            else if (!strcmp(tag, "encoding")) {
                if (!strcasecmp(tag_val, "none")) encode = E_NONE;
                else if (!strcasecmp(tag_val, "url")) encode = E_URL;
                else if (!strcasecmp(tag_val, "entity")) encode = E_ENTITY;
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "unknown value \"%s\" to parameter \"encoding\" of "
                           "tag echo in %s", tag_val, r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" in tag echo of %s",
                            tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }

        }
    }
    return 0;
}

/* error and tf must point to a string with room for at 
 * least MAX_STRING_LEN characters 
 */
static int handle_config(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                         request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                         apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    char *parsed_string;
    apr_table_t *env = r->subprocess_env;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 0);
            if (tag_val == NULL) {
                if (tag == NULL) {
                    return 0;  /* Reached the end of the string. */
                }
                else {
                    return 1;  /* tags must have values. */
                }
            }
            if (!strcmp(tag, "errmsg")) {
                if (ctx->error_str_override == NULL) {
                    ctx->error_str_override = (char *)apr_palloc(ctx->pool,
                                                              MAX_STRING_LEN);
                    ctx->error_str = ctx->error_str_override;
                }
                ap_ssi_parse_string(r, ctx, tag_val, ctx->error_str_override,
                                    MAX_STRING_LEN, 0);
            }
            else if (!strcmp(tag, "timefmt")) {
                apr_time_t date = r->request_time;
                if (ctx->time_str_override == NULL) {
                    ctx->time_str_override = (char *)apr_palloc(ctx->pool,
                                                              MAX_STRING_LEN);
                    ctx->time_str = ctx->time_str_override;
                }
                ap_ssi_parse_string(r, ctx, tag_val, ctx->time_str_override,
                                    MAX_STRING_LEN, 0);
                apr_table_setn(env, "DATE_LOCAL", ap_ht_time(r->pool, date, 
                               ctx->time_str, 0));
                apr_table_setn(env, "DATE_GMT", ap_ht_time(r->pool, date, 
                               ctx->time_str, 1));
                apr_table_setn(env, "LAST_MODIFIED",
                               ap_ht_time(r->pool, r->finfo.mtime, 
                               ctx->time_str, 0));
            }
            else if (!strcmp(tag, "sizefmt")) {
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                decodehtml(parsed_string);
                if (!strcmp(parsed_string, "bytes")) {
                    ctx->flags |= FLAG_SIZE_IN_BYTES;
                }
                else if (!strcmp(parsed_string, "abbrev")) {
                    ctx->flags &= FLAG_SIZE_ABBREV;
                }
            }
            else {
                apr_bucket *tmp_buck;

                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "unknown parameter \"%s\" to tag config in %s",
                              tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }
        }
    }
    return 0;
}


static int find_file(request_rec *r, const char *directive, const char *tag,
                     char *tag_val, apr_finfo_t *finfo)
{
    char *to_send = tag_val;
    request_rec *rr = NULL;
    int ret=0;
    char *error_fmt = NULL;
    apr_status_t rv = APR_SUCCESS;

    if (!strcmp(tag, "file")) {
        /* XXX: Port to apr_filepath_merge
         * be safe; only files in this directory or below allowed 
         */
        if (!is_only_below(tag_val)) {
            error_fmt = "unable to access file \"%s\" "
                        "in parsed file %s";
        }
        else {
            ap_getparents(tag_val);    /* get rid of any nasties */

            /* note: it is okay to pass NULL for the "next filter" since
               we never attempt to "run" this sub request. */
            rr = ap_sub_req_lookup_file(tag_val, r, NULL);

            if (rr->status == HTTP_OK && rr->finfo.filetype != 0) {
                to_send = rr->filename;
                if ((rv = apr_stat(finfo, to_send, 
                    APR_FINFO_GPROT | APR_FINFO_MIN, rr->pool)) != APR_SUCCESS
                    && rv != APR_INCOMPLETE) {
                    error_fmt = "unable to get information about \"%s\" "
                        "in parsed file %s";
                }
            }
            else {
                error_fmt = "unable to lookup information about \"%s\" "
                            "in parsed file %s";
            }
        }

        if (error_fmt) {
            ret = -1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR,
                          rv, r, error_fmt, to_send, r->filename);
        }

        if (rr) ap_destroy_sub_req(rr);
        
        return ret;
    }
    else if (!strcmp(tag, "virtual")) {
        /* note: it is okay to pass NULL for the "next filter" since
           we never attempt to "run" this sub request. */
        rr = ap_sub_req_lookup_uri(tag_val, r, NULL);

        if (rr->status == HTTP_OK && rr->finfo.filetype != 0) {
            memcpy((char *) finfo, (const char *) &rr->finfo,
                   sizeof(rr->finfo));
            ap_destroy_sub_req(rr);
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "unable to get information about \"%s\" "
                        "in parsed file %s",
                        tag_val, r->filename);
            ap_destroy_sub_req(rr);
            return -1;
        }
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "unknown parameter \"%s\" to tag %s in %s",
                    tag, directive, r->filename);
        return -1;
    }
}

static int handle_fsize(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                        request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                        apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    apr_finfo_t  finfo;
    apr_size_t  s_len;
    apr_bucket   *tmp_buck;
    char *parsed_string;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
            if (tag_val == NULL) {
                if (tag == NULL) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else {
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                if (!find_file(r, "fsize", tag, parsed_string, &finfo)) {
                    /* XXX: if we *know* we're going to have to copy the
                     * thing off of the stack anyway, why not palloc buff
                     * instead of sticking it on the stack; then we can just
                     * use a pool bucket and skip the copy
                     */
                    char buff[50];

                    if (!(ctx->flags & FLAG_SIZE_IN_BYTES)) {
                        apr_strfsize(finfo.size, buff);
                        s_len = strlen (buff);
                    }
                    else {
                        int l, x, pos = 0;
                        char tmp_buff[50];

                        apr_snprintf(tmp_buff, sizeof(tmp_buff), 
                                     "%" APR_OFF_T_FMT, finfo.size);
                        l = strlen(tmp_buff);    /* grrr */
                        for (x = 0; x < l; x++) {
                            if (x && (!((l - x) % 3))) {
                                buff[pos++] = ',';
                            }
                            buff[pos++] = tmp_buff[x];
                        }
                        buff[pos] = '\0';
                        s_len = pos;
                    }

                    tmp_buck = apr_bucket_heap_create(buff, s_len, NULL,
                                                  r->connection->bucket_alloc);
                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
                    if (*inserted_head == NULL) {
                        *inserted_head = tmp_buck;
                    }
                }
                else {
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
            }
        }
    }
    return 0;
}

static int handle_flastmod(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                           request_rec *r, ap_filter_t *f, 
                           apr_bucket *head_ptr, apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    apr_finfo_t  finfo;
    apr_size_t  t_len;
    apr_bucket   *tmp_buck;
    char *parsed_string;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
            if (tag_val == NULL) {
                if (tag == NULL) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else {
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                if (!find_file(r, "flastmod", tag, parsed_string, &finfo)) {
                    char *t_val;

                    t_val = ap_ht_time(r->pool, finfo.mtime, ctx->time_str, 0);
                    t_len = strlen(t_val);

                    tmp_buck = apr_bucket_pool_create(t_val, t_len, r->pool,
                                                  r->connection->bucket_alloc);
                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
                    if (*inserted_head == NULL) {
                        *inserted_head = tmp_buck;
                    }
                }
                else {
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
            }
        }
    }
    return 0;
}

static int re_check(request_rec *r, include_ctx_t *ctx, 
                    char *string, char *rexp)
{
    regex_t *compiled;
    const apr_size_t nres = sizeof(*ctx->re_result) / sizeof(regmatch_t);
    int regex_error;

    compiled = ap_pregcomp(r->pool, rexp, REG_EXTENDED | REG_NOSUB);
    if (compiled == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "unable to compile pattern \"%s\"", rexp);
        return -1;
    }
    if (!ctx->re_result) {
        ctx->re_result = apr_pcalloc(r->pool, sizeof(*ctx->re_result));
    }
    ctx->re_string = string;
    regex_error = ap_regexec(compiled, string, nres, *ctx->re_result, 0);
    ap_pregfree(r->pool, compiled);
    return (!regex_error);
}

enum token_type {
    token_string, token_re,
    token_and, token_or, token_not, token_eq, token_ne,
    token_rbrace, token_lbrace, token_group,
    token_ge, token_le, token_gt, token_lt
};
struct token {
    enum token_type type;
    char* value;
};

static const char *get_ptoken(request_rec *r, const char *string, 
                              struct token *token, int *unmatched)
{
    char ch;
    int next = 0;
    char qs = 0;
    int tkn_fnd = 0;

    token->value = NULL;

    /* Skip leading white space */
    if (string == (char *) NULL) {
        return (char *) NULL;
    }
    while ((ch = *string++)) {
        if (!apr_isspace(ch)) {
            break;
        }
    }
    if (ch == '\0') {
        return (char *) NULL;
    }

    token->type = token_string; /* the default type */
    switch (ch) {
    case '(':
        token->type = token_lbrace;
        return (string);
    case ')':
        token->type = token_rbrace;
        return (string);
    case '=':
        token->type = token_eq;
        return (string);
    case '!':
        if (*string == '=') {
            token->type = token_ne;
            return (string + 1);
        }
        else {
            token->type = token_not;
            return (string);
        }
    case '\'':
        /* already token->type == token_string */
        qs = '\'';
        break;
    case '/':
        token->type = token_re;
        qs = '/';
        break;
    case '|':
        if (*string == '|') {
            token->type = token_or;
            return (string + 1);
        }
        break;
    case '&':
        if (*string == '&') {
            token->type = token_and;
            return (string + 1);
        }
        break;
    case '>':
        if (*string == '=') {
            token->type = token_ge;
            return (string + 1);
        }
        else {
            token->type = token_gt;
            return (string);
        }
    case '<':
        if (*string == '=') {
            token->type = token_le;
            return (string + 1);
        }
        else {
            token->type = token_lt;
            return (string);
        }
    default:
        /* already token->type == token_string */
        break;
    }
    /* We should only be here if we are in a string */
    token->value = apr_palloc(r->pool, strlen(string) + 2); /* 2 for ch plus
                                                               trailing null */
    if (!qs) {
        --string;
    }

    /* 
     * I used the ++string throughout this section so that string
     * ends up pointing to the next token and I can just return it
     */
    for (ch = *string; ((ch != '\0') && (!tkn_fnd)); ch = *++string) {
        if (ch == '\\') {
            if ((ch = *++string) == '\0') {
                tkn_fnd = 1;
            }
            else {
                token->value[next++] = ch;
            }
        }
        else {
            if (!qs) {
                if (apr_isspace(ch)) {
                    tkn_fnd = 1;
                }
                else {
                    switch (ch) {
                    case '(':
                    case ')':
                    case '=':
                    case '!':
                    case '<':
                    case '>':
                        tkn_fnd = 1;
                        break;
                    case '|':
                        if (*(string + 1) == '|') {
                            tkn_fnd = 1;
                        }
                        break;
                    case '&':
                        if (*(string + 1) == '&') {
                            tkn_fnd = 1;
                        }
                        break;
                    }
                    if (!tkn_fnd) {
                        token->value[next++] = ch;
                    }
                }
            }
            else {
                if (ch == qs) {
                    qs = 0;
                    tkn_fnd = 1;
                    string++;
                }
                else {
                    token->value[next++] = ch;
                }
            }
        }
        if (tkn_fnd) {
            break;
        }
    }

    /* If qs is still set, we have an unmatched quote */
    if (qs) {
        *unmatched = 1;
        next = 0;
    }
    token->value[next] = '\0';

    return (string);
}


/* there is an implicit assumption here that expr is at most MAX_STRING_LEN-1
 * characters long...
 */
static int parse_expr(request_rec *r, include_ctx_t *ctx, const char *expr,
                      int *was_error, int *was_unmatched, char *debug)
{
    struct parse_node {
        struct parse_node *left, *right, *parent;
        struct token token;
        int value, done;
    } *root, *current, *new;
    const char *parse;
    char* buffer;
    int retval = 0;
    apr_size_t debug_pos = 0;

    debug[debug_pos] = '\0';
    *was_error       = 0;
    *was_unmatched   = 0;
    if ((parse = expr) == (char *) NULL) {
        return (0);
    }
    root = current = (struct parse_node *) NULL;

    /* Create Parse Tree */
    while (1) {
        new = (struct parse_node *) apr_palloc(r->pool,
                                           sizeof(struct parse_node));
        new->parent = new->left = new->right = (struct parse_node *) NULL;
        new->done = 0;
        if ((parse = get_ptoken(r, parse, &new->token, was_unmatched)) == 
            (char *) NULL) {
            break;
        }
        switch (new->token.type) {

        case token_string:
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], 
                                  "     Token: string (%s)\n", 
                                  new->token.value);
#endif
            if (current == (struct parse_node *) NULL) {
                root = current = new;
                break;
            }
            switch (current->token.type) {
            case token_string:
                current->token.value = apr_pstrcat(r->pool,
                                                   current->token.value,
                                                   current->token.value[0] ? " " : "",
                                                   new->token.value,
                                                   NULL);
                                                   
                break;
            case token_eq:
            case token_ne:
            case token_and:
            case token_or:
            case token_lbrace:
            case token_not:
            case token_ge:
            case token_gt:
            case token_le:
            case token_lt:
                new->parent = current;
                current = current->right = new;
                break;
            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            break;

        case token_re:
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], 
                                  "     Token: regex (%s)\n", 
                                  new->token.value);
#endif
            if (current == (struct parse_node *) NULL) {
                root = current = new;
                break;
            }
            switch (current->token.type) {
            case token_eq:
            case token_ne:
            case token_and:
            case token_or:
            case token_lbrace:
            case token_not:
                new->parent = current;
                current = current->right = new;
                break;
            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            break;

        case token_and:
        case token_or:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Token: and/or\n",
                    sizeof ("     Token: and/or\n"));
            debug_pos += sizeof ("     Token: and/or\n");
#endif
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            /* Percolate upwards */
            while (current != (struct parse_node *) NULL) {
                switch (current->token.type) {
                case token_string:
                case token_re:
                case token_group:
                case token_not:
                case token_eq:
                case token_ne:
                case token_and:
                case token_or:
                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                    current = current->parent;
                    continue;
                case token_lbrace:
                    break;
                default:
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                "Invalid expression \"%s\" in file %s",
                                expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
                break;
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
            }
            else {
                new->left = current->right;
                new->left->parent = new;
                current->right = new;
                new->parent = current;
            }
            current = new;
            break;

        case token_not:
#ifdef DEBUG_INCLUDE
            memcpy(&debug[debug_pos], "     Token: not\n",
                    sizeof("     Token: not\n"));
            debug_pos += sizeof("     Token: not\n");
#endif
            if (current == (struct parse_node *) NULL) {
                root = current = new;
                break;
            }
            /* Percolate upwards */
            if (current != (struct parse_node *) NULL) {
                switch (current->token.type) {
                case token_not:
                case token_eq:
                case token_ne:
                case token_and:
                case token_or:
                case token_lbrace:
                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                    break;
                default:
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Invalid expression \"%s\" in file %s",
                                  expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
            }
            else {
                new->left = current->right;
                current->right = new;
                new->parent = current;
            }
            current = new;
            break;

        case token_eq:
        case token_ne:
        case token_ge:
        case token_gt:
        case token_le:
        case token_lt:
#ifdef DEBUG_INCLUDE
            memcpy(&debug[debug_pos], "     Token: eq/ne/ge/gt/le/lt\n",
                    sizeof("     Token: eq/ne/ge/gt/le/lt\n"));
            debug_pos += sizeof("     Token: eq/ne/ge/gt/le/lt\n");
#endif
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Invalid expression \"%s\" in file %s",
                              expr, r->filename);
                *was_error = 1;
                return retval;
            }
            /* Percolate upwards */
            while (current != (struct parse_node *) NULL) {
                switch (current->token.type) {
                case token_string:
                case token_re:
                case token_group:
                    current = current->parent;
                    continue;
                case token_lbrace:
                case token_and:
                case token_or:
                    break;
                case token_not:
                case token_eq:
                case token_ne:
                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                default:
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                "Invalid expression \"%s\" in file %s",
                                expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
                break;
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
            }
            else {
                new->left = current->right;
                new->left->parent = new;
                current->right = new;
                new->parent = current;
            }
            current = new;
            break;

        case token_rbrace:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Token: rbrace\n",
                    sizeof ("     Token: rbrace\n"));
            debug_pos += sizeof ("     Token: rbrace\n");
#endif
            while (current != (struct parse_node *) NULL) {
                if (current->token.type == token_lbrace) {
                    current->token.type = token_group;
                    break;
                }
                current = current->parent;
            }
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Unmatched ')' in \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            break;

        case token_lbrace:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Token: lbrace\n",
                    sizeof ("     Token: lbrace\n"));
            debug_pos += sizeof ("     Token: lbrace\n");
#endif
            if (current == (struct parse_node *) NULL) {
                root = current = new;
                break;
            }
            /* Percolate upwards */
            if (current != (struct parse_node *) NULL) {
                switch (current->token.type) {
                case token_not:
                case token_eq:
                case token_ne:
                case token_and:
                case token_or:
                case token_lbrace:
                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                    break;
                case token_string:
                case token_re:
                case token_group:
                default:
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                "Invalid expression \"%s\" in file %s",
                                expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
            }
            else {
                new->left = current->right;
                current->right = new;
                new->parent = current;
            }
            current = new;
            break;
        default:
            break;
        }
    }

    /* Evaluate Parse Tree */
    current = root;
    while (current != (struct parse_node *) NULL) {
        switch (current->token.type) {
        case token_string:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Evaluate string\n",
                    sizeof ("     Evaluate string\n"));
            debug_pos += sizeof ("     Evaluate string\n");
#endif
            buffer = ap_ssi_parse_string(r, ctx, current->token.value, NULL, 
                                         MAX_STRING_LEN, 0);
            current->token.value = buffer;
            current->value = (current->token.value[0] != '\0');
            current->done = 1;
            current = current->parent;
            break;

        case token_re:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "No operator before regex of expr \"%s\" in file %s",
                          expr, r->filename);
            *was_error = 1;
            return retval;

        case token_and:
        case token_or:
#ifdef DEBUG_INCLUDE
            memcpy(&debug[debug_pos], "     Evaluate and/or\n",
                    sizeof("     Evaluate and/or\n"));
            debug_pos += sizeof("     Evaluate and/or\n");
#endif
            if (current->left  == (struct parse_node *) NULL ||
                current->right == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Invalid expression \"%s\" in file %s",
                              expr, r->filename);
                *was_error = 1;
                return retval;
            }
            if (!current->left->done) {
                switch (current->left->token.type) {
                case token_string:
                    buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
                                                 NULL, MAX_STRING_LEN, 0);
                    current->left->token.value = buffer;
                    current->left->value = 
                                       (current->left->token.value[0] != '\0');
                    current->left->done = 1;
                    break;
                default:
                    current = current->left;
                    continue;
                }
            }
            if (!current->right->done) {
                switch (current->right->token.type) {
                case token_string:
                    buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
                                                 NULL, MAX_STRING_LEN, 0);
                    current->right->token.value = buffer;
                    current->right->value = 
                                      (current->right->token.value[0] != '\0');
                    current->right->done = 1;
                    break;
                default:
                    current = current->right;
                    continue;
                }
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Left: %c\n",
                                  current->left->value ? '1' : '0');
            debug_pos += sprintf (&debug[debug_pos], "     Right: %c\n",
                                  current->right->value ? '1' : '0');
#endif
            if (current->token.type == token_and) {
                current->value = current->left->value && current->right->value;
            }
            else {
                current->value = current->left->value || current->right->value;
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_eq:
        case token_ne:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Evaluate eq/ne\n",
                    sizeof ("     Evaluate eq/ne\n"));
            debug_pos += sizeof ("     Evaluate eq/ne\n");
#endif
            if ((current->left == (struct parse_node *) NULL) ||
                (current->right == (struct parse_node *) NULL) ||
                (current->left->token.type != token_string) ||
                ((current->right->token.type != token_string) &&
                 (current->right->token.type != token_re))) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
                                         NULL, MAX_STRING_LEN, 0);
            current->left->token.value = buffer;
            buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
                                         NULL, MAX_STRING_LEN, 0);
            current->right->token.value = buffer;
            if (current->right->token.type == token_re) {
#ifdef DEBUG_INCLUDE
                debug_pos += sprintf (&debug[debug_pos],
                                      "     Re Compare (%s) with /%s/\n",
                                      current->left->token.value,
                                      current->right->token.value);
#endif
                current->value =
                    re_check(r, ctx, current->left->token.value,
                             current->right->token.value);
            }
            else {
#ifdef DEBUG_INCLUDE
                debug_pos += sprintf (&debug[debug_pos],
                                      "     Compare (%s) with (%s)\n",
                                      current->left->token.value,
                                      current->right->token.value);
#endif
                current->value =
                    (strcmp(current->left->token.value,
                            current->right->token.value) == 0);
            }
            if (current->token.type == token_ne) {
                current->value = !current->value;
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;
        case token_ge:
        case token_gt:
        case token_le:
        case token_lt:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Evaluate ge/gt/le/lt\n",
                    sizeof ("     Evaluate ge/gt/le/lt\n"));
            debug_pos += sizeof ("     Evaluate ge/gt/le/lt\n");
#endif
            if ((current->left == (struct parse_node *) NULL) ||
                (current->right == (struct parse_node *) NULL) ||
                (current->left->token.type != token_string) ||
                (current->right->token.type != token_string)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
                                         NULL, MAX_STRING_LEN, 0);
            current->left->token.value = buffer;
            buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
                                         NULL, MAX_STRING_LEN, 0);
            current->right->token.value = buffer;
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos],
                                  "     Compare (%s) with (%s)\n",
                                  current->left->token.value,
                                  current->right->token.value);
#endif
            current->value =
                strcmp(current->left->token.value,
                       current->right->token.value);
            if (current->token.type == token_ge) {
                current->value = current->value >= 0;
            }
            else if (current->token.type == token_gt) {
                current->value = current->value > 0;
            }
            else if (current->token.type == token_le) {
                current->value = current->value <= 0;
            }
            else if (current->token.type == token_lt) {
                current->value = current->value < 0;
            }
            else {
                current->value = 0;     /* Don't return -1 if unknown token */
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_not:
            if (current->right != (struct parse_node *) NULL) {
                if (!current->right->done) {
                    current = current->right;
                    continue;
                }
                current->value = !current->right->value;
            }
            else {
                current->value = 0;
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Evaluate !: %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_group:
            if (current->right != (struct parse_node *) NULL) {
                if (!current->right->done) {
                    current = current->right;
                    continue;
                }
                current->value = current->right->value;
            }
            else {
                current->value = 1;
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Evaluate (): %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_lbrace:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "Unmatched '(' in \"%s\" in file %s",
                        expr, r->filename);
            *was_error = 1;
            return retval;

        case token_rbrace:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "Unmatched ')' in \"%s\" in file %s",
                        expr, r->filename);
            *was_error = 1;
            return retval;

        default:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "bad token type");
            *was_error = 1;
            return retval;
        }
    }

    retval = (root == (struct parse_node *) NULL) ? 0 : root->value;
    return (retval);
}

/*-------------------------------------------------------------------------*/
#ifdef DEBUG_INCLUDE

#define MAX_DEBUG_SIZE MAX_STRING_LEN
#define LOG_COND_STATUS(cntx, t_buck, h_ptr, ins_head, tag_text)           \
{                                                                          \
    char cond_txt[] = "**** X     conditional_status=\"0\"\n";             \
                                                                           \
    if (cntx->flags & FLAG_COND_TRUE) {                                    \
        cond_txt[31] = '1';                                                \
    }                                                                      \
    memcpy(&cond_txt[5], tag_text, sizeof(tag_text)-1);                    \
    t_buck = apr_bucket_heap_create(cond_txt, sizeof(cond_txt)-1,          \
                                    NULL, h_ptr->list);                    \
    APR_BUCKET_INSERT_BEFORE(h_ptr, t_buck);                               \
                                                                           \
    if (ins_head == NULL) {                                                \
        ins_head = t_buck;                                                 \
    }                                                                      \
}
#define DUMP_PARSE_EXPR_DEBUG(t_buck, h_ptr, d_buf, ins_head)            \
{                                                                        \
    if (d_buf[0] != '\0') {                                              \
        t_buck = apr_bucket_heap_create(d_buf, strlen(d_buf),            \
                                        NULL, h_ptr->list);              \
        APR_BUCKET_INSERT_BEFORE(h_ptr, t_buck);                         \
                                                                         \
        if (ins_head == NULL) {                                          \
            ins_head = t_buck;                                           \
        }                                                                \
    }                                                                    \
}
#else

#define MAX_DEBUG_SIZE 10
#define LOG_COND_STATUS(cntx, t_buck, h_ptr, ins_head, tag_text)
#define DUMP_PARSE_EXPR_DEBUG(t_buck, h_ptr, d_buf, ins_head)

#endif
/*-------------------------------------------------------------------------*/

/* pjr - These seem to allow expr="fred" expr="joe" where joe overwrites fred. */
static int handle_if(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                     request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                     apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    char *expr    = NULL;
    int   expr_ret, was_error, was_unmatched;
    apr_bucket *tmp_buck;
    char debug_buf[MAX_DEBUG_SIZE];

    *inserted_head = NULL;
    if (!(ctx->flags & FLAG_PRINTING)) {
        ctx->if_nesting_level++;
    }
    else {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 0);
            if (tag == NULL) {
                if (expr == NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "missing expr in if statement: %s", 
                                  r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
                expr_ret = parse_expr(r, ctx, expr, &was_error, 
                                      &was_unmatched, debug_buf);
                if (was_error) {
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
                if (was_unmatched) {
                    DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, 
                                          "\nUnmatched '\n", *inserted_head);
                }
                DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, debug_buf, 
                                      *inserted_head);
                
                if (expr_ret) {
                    ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
                }
                else {
                    ctx->flags &= FLAG_CLEAR_PRINT_COND;
                }
                LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, 
                                "   if");
                ctx->if_nesting_level = 0;
                return 0;
            }
            else if (!strcmp(tag, "expr")) {
                expr = tag_val;
#ifdef DEBUG_INCLUDE
                if (1) {
                    apr_size_t d_len = 0;
                    d_len = sprintf(debug_buf, "**** if expr=\"%s\"\n", expr);
                    tmp_buck = apr_bucket_heap_create(debug_buf, d_len, NULL,
                                                  r->connection->bucket_alloc);
                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);

                    if (*inserted_head == NULL) {
                        *inserted_head = tmp_buck;
                    }
                }
#endif
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" to tag if in %s", tag, 
                            r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }

        }
    }
    return 0;
}

static int handle_elif(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                       apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    char *expr    = NULL;
    int   expr_ret, was_error, was_unmatched;
    apr_bucket *tmp_buck;
    char debug_buf[MAX_DEBUG_SIZE];

    *inserted_head = NULL;
    if (!ctx->if_nesting_level) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 0);
            if (tag == '\0') {
                LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, 
                                " elif");
                
                if (ctx->flags & FLAG_COND_TRUE) {
                    ctx->flags &= FLAG_CLEAR_PRINTING;
                    return (0);
                }
                if (expr == NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "missing expr in elif statement: %s", 
                                  r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
                expr_ret = parse_expr(r, ctx, expr, &was_error, 
                                      &was_unmatched, debug_buf);
                if (was_error) {
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
                if (was_unmatched) {
                    DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, 
                                          "\nUnmatched '\n", *inserted_head);
                }
                DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, debug_buf, 
                                      *inserted_head);
                
                if (expr_ret) {
                    ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
                }
                else {
                    ctx->flags &= FLAG_CLEAR_PRINT_COND;
                }
                LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, 
                                " elif");
                return (0);
            }
            else if (!strcmp(tag, "expr")) {
                expr = tag_val;
#ifdef DEBUG_INCLUDE
                if (1) {
                    apr_size_t d_len = 0;
                    d_len = sprintf(debug_buf, "**** elif expr=\"%s\"\n", expr);
                    tmp_buck = apr_bucket_heap_create(debug_buf, d_len, NULL,
                                                  r->connection->bucket_alloc);
                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);

                    if (*inserted_head == NULL) {
                        *inserted_head = tmp_buck;
                    }
                }
#endif
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                               "unknown parameter \"%s\" to tag if in %s", tag, 
                               r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }
        }
    }
    return 0;
}

static int handle_else(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                       apr_bucket **inserted_head)
{
    char *tag = NULL;
    char *tag_val = NULL;
    apr_bucket *tmp_buck;

    *inserted_head = NULL;
    if (!ctx->if_nesting_level) {
        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
        if ((tag != NULL) || (tag_val != NULL)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "else directive does not take tags in %s", r->filename);
            if (ctx->flags & FLAG_PRINTING) {
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            }
            return -1;
        }
        else {
            LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, " else");
            
            if (ctx->flags & FLAG_COND_TRUE) {
                ctx->flags &= FLAG_CLEAR_PRINTING;
            }
            else {
                ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
            }
            return 0;
        }
    }
    return 0;
}

static int handle_endif(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                        request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                        apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    apr_bucket *tmp_buck;

    *inserted_head = NULL;
    if (!ctx->if_nesting_level) {
        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
        if ((tag != NULL) || (tag_val != NULL)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "endif directive does not take tags in %s", r->filename);
            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            return -1;
        }
        else {
            LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, "endif");
            ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
            return 0;
        }
    }
    else {
        ctx->if_nesting_level--;
        return 0;
    }
}

static int handle_set(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                      request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                      apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    char *var     = NULL;
    apr_bucket *tmp_buck;
    char *parsed_string;
    request_rec *sub = r->main;
    apr_pool_t *p = r->pool;

    /* we need to use the 'main' request pool to set notes as that is 
     * a notes lifetime
     */
    while (sub) {
        p = sub->pool;
        sub = sub->main;
    }

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
            if ((tag == NULL) && (tag_val == NULL)) {
                return 0;
            }
            else if (tag_val == NULL) {
                return 1;
            }
            else if (!strcmp(tag, "var")) {
                var = ap_ssi_parse_string(r, ctx, tag_val, NULL,
                                          MAX_STRING_LEN, 0);
            }
            else if (!strcmp(tag, "value")) {
                if (var == (char *) NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "variable must precede value in set directive in %s",
                           r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return (-1);
                }
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                apr_table_setn(r->subprocess_env, apr_pstrdup(p, var),
                               apr_pstrdup(p, parsed_string));
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid tag for set directive in %s", r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return -1;
            }
        }
    }
    return 0;
}

static int handle_printenv(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                           request_rec *r, ap_filter_t *f, 
                           apr_bucket *head_ptr, apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    apr_bucket *tmp_buck;

    if (ctx->flags & FLAG_PRINTING) {
        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
        if ((tag == NULL) && (tag_val == NULL)) {
            const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
            const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
            int i;
            const char *key_text, *val_text;
            char *key_val, *next;
            apr_size_t   k_len, v_len, kv_length;

            *inserted_head = NULL;
            for (i = 0; i < arr->nelts; ++i) {
                key_text = ap_escape_html(r->pool, elts[i].key);
                val_text = elts[i].val;
                if (val_text == LAZY_VALUE) {
                    val_text = add_include_vars_lazy(r, elts[i].key, ctx->time_str);
                }
                val_text = ap_escape_html(r->pool, elts[i].val);
                k_len = strlen(key_text);
                v_len = strlen(val_text);
                kv_length = k_len + v_len + sizeof("=\n");
                key_val = apr_palloc(r->pool, kv_length);
                next = key_val;
                memcpy(next, key_text, k_len);
                next += k_len;
                *next++ = '=';
                memcpy(next, val_text, v_len);
                next += v_len;
                *next++ = '\n';
                *next = 0;
                tmp_buck = apr_bucket_pool_create(key_val, kv_length - 1,
                                                  r->pool,
                                                  r->connection->bucket_alloc);
                APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
                if (*inserted_head == NULL) {
                    *inserted_head = tmp_buck;
                }
            }
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "printenv directive does not take tags in %s", 
                        r->filename);
            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            return -1;
        }
    }
    return 0;
}

/* -------------------------- The main function --------------------------- */

/*
 * returns the index position of the first byte of start_seq (or the len of
 * the buffer as non-match)
 */
static apr_size_t find_start_sequence(ssi_ctx_t *ctx, const char *data,
                                      apr_size_t len)
{
    apr_size_t slen = ctx->ctx->start_seq_len;
    apr_size_t index;
    const char *p, *ep;

    if (len < slen) {
        p = data; /* try partial match at the end of the buffer (below) */
    }
    else {
        /* try fast bndm search over the buffer
         * (hopefully the whole start sequence can be found in this buffer)
         */
        index = bndm(ctx->ctx->start_seq, ctx->ctx->start_seq_len, data, len,
                     ctx->ctx->start_seq_pat);

        /* wow, found it. ready. */
        if (index < len) {
            ctx->state = PARSE_DIRECTIVE;
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
        while (p < ep && *p != *ctx->ctx->start_seq) {
            ++p;
        }

        index = p - data;

        /* found a possible start_seq start */
        if (p < ep) {
            apr_size_t pos = 1;

            ++p;
            while (p < ep && *p == ctx->ctx->start_seq[pos]) {
                ++p;
                ++pos;
            }

            /* partial match found. Store the info for the next round */
            if (p == ep) {
                ctx->state = PARSE_HEAD;
                ctx->ctx->parse_pos = pos;
                return index;
            }
        }

        /* we must try all combinations; consider (e.g.) SSIStartTag "--->"
         * and a string data of "--.-" and the end of the buffer

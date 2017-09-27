     rr->path_info = r->path_info;       /* hard to get right; see mod_cgi.c */
     rr->args = r->args;
 
     /* Force sub_req to be treated as a CGI request, even if ordinary
      * typing rules would have called it something else.
      */
-
     ap_set_content_type(rr, CGI_MAGIC_TYPE);
 
     /* Run it. */
-
     rr_status = ap_run_sub_req(rr);
     if (ap_is_HTTP_REDIRECT(rr_status)) {
-        apr_size_t len_loc;
         const char *location = apr_table_get(rr->headers_out, "Location");
-        conn_rec *c = r->connection;
 
-        location = ap_escape_html(rr->pool, location);
-        len_loc = strlen(location);
+        if (location) {
+            char *buffer;
 
-        /* XXX: if most of this stuff is going to get copied anyway,
-         * it'd be more efficient to pstrcat it into a single pool buffer
-         * and a single pool bucket */
-
-        tmp_buck = apr_bucket_immortal_create("<A HREF=\"",
-                                              sizeof("<A HREF=\"") - 1,
-                                              c->bucket_alloc);
-        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
-        tmp2_buck = apr_bucket_heap_create(location, len_loc, NULL,
-                                           c->bucket_alloc);
-        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
-        tmp2_buck = apr_bucket_immortal_create("\">", sizeof("\">") - 1,
-                                               c->bucket_alloc);
-        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
-        tmp2_buck = apr_bucket_heap_create(location, len_loc, NULL,
-                                           c->bucket_alloc);
-        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
-        tmp2_buck = apr_bucket_immortal_create("</A>", sizeof("</A>") - 1,
-                                               c->bucket_alloc);
-        APR_BUCKET_INSERT_BEFORE(head_ptr, tmp2_buck);
-
-        if (*inserted_head == NULL) {
-            *inserted_head = tmp_buck;
+            location = ap_escape_html(rr->pool, location);
+            buffer = apr_pstrcat(ctx->pool, "<a href=\"", location, "\">",
+                                 location, "</a>", NULL);
+
+            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(buffer,
+                                    strlen(buffer), ctx->pool,
+                                    f->c->bucket_alloc));
         }
     }
 
     ap_destroy_sub_req(rr);
 
-    return 0;
+    return APR_SUCCESS;
 }
 
-
-static int include_cmd(include_ctx_t *ctx, apr_bucket_brigade **bb,
-                       const char *command, request_rec *r, ap_filter_t *f)
+static apr_status_t include_cmd(include_ctx_t *ctx, ap_filter_t *f,
+                                apr_bucket_brigade *bb, const char *command)
 {
     cgi_exec_info_t  e_info;
-    const char   **argv;
-    apr_file_t    *script_out = NULL, *script_in = NULL, *script_err = NULL;
-    apr_bucket_brigade *bcgi;
-    apr_bucket *b;
+    const char **argv;
+    apr_file_t *script_out = NULL, *script_in = NULL, *script_err = NULL;
     apr_status_t rv;
+    request_rec *r = f->r;
 
     add_ssi_vars(r);
 
     e_info.process_cgi = 0;
     e_info.cmd_type    = APR_SHELLCMD;
     e_info.detached    = 0;
     e_info.in_pipe     = APR_NO_PIPE;
     e_info.out_pipe    = APR_FULL_BLOCK;
     e_info.err_pipe    = APR_NO_PIPE;
     e_info.prog_type   = RUN_AS_SSI;
-    e_info.bb          = bb;
+    e_info.bb          = &bb;
     e_info.ctx         = ctx;
     e_info.next        = f->next;
+    e_info.addrspace   = 0;
 
-    if ((rv = cgi_build_command(&command, &argv, r, r->pool, &e_info)) != APR_SUCCESS) {
+    if ((rv = cgi_build_command(&command, &argv, r, r->pool,
+                                &e_info)) != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                      "don't know how to spawn cmd child process: %s", 
+                      "don't know how to spawn cmd child process: %s",
                       r->filename);
-        return HTTP_INTERNAL_SERVER_ERROR;
+        return rv;
     }
 
     /* run the script in its own process */
     if ((rv = run_cgi_child(&script_out, &script_in, &script_err,
                             command, argv, r, r->pool,
                             &e_info)) != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                       "couldn't spawn child process: %s", r->filename);
-        return HTTP_INTERNAL_SERVER_ERROR;
+        return rv;
     }
 
-    bcgi = apr_brigade_create(r->pool, f->c->bucket_alloc);
-    b = apr_bucket_pipe_create(script_in, f->c->bucket_alloc);
-    APR_BRIGADE_INSERT_TAIL(bcgi, b);
-    ap_pass_brigade(f->next, bcgi);
+    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pipe_create(script_in,
+                            f->c->bucket_alloc));
+    ctx->flush_now = 1;
 
     /* We can't close the pipe here, because we may return before the
      * full CGI has been sent to the network.  That's okay though,
      * because we can rely on the pool to close the pipe for us.
      */
-
-    return 0;
+    return APR_SUCCESS;
 }
 
-static int handle_exec(include_ctx_t *ctx, apr_bucket_brigade **bb,
-                       request_rec *r, ap_filter_t *f, apr_bucket *head_ptr,
-                       apr_bucket **inserted_head)
+static apr_status_t handle_exec(include_ctx_t *ctx, ap_filter_t *f,
+                                apr_bucket_brigade *bb)
 {
-    char *tag     = NULL;
+    char *tag = NULL;
     char *tag_val = NULL;
+    request_rec *r = f->r;
     char *file = r->filename;
-    apr_bucket  *tmp_buck;
     char parsed_string[MAX_STRING_LEN];
 
-    *inserted_head = NULL;
-    if (ctx->flags & FLAG_PRINTING) {
-        if (ctx->flags & FLAG_NO_EXEC) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "exec used but not allowed in %s", r->filename);
-            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
+    if (!ctx->argc) {
+        ap_log_rerror(APLOG_MARK,
+                      (ctx->flags & SSI_FLAG_PRINTING)
+                          ? APLOG_ERR : APLOG_WARNING,
+                      0, r, "missing argument for exec element in %s",
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
+    if (ctx->flags & SSI_FLAG_NO_EXEC) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "exec used but not allowed "
+                      "in %s", r->filename);
+        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+        return APR_SUCCESS;
+    }
+
+    while (1) {
+        cgi_pfn_gtv(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
+        if (!tag || !tag_val) {
+            break;
+        }
+
+        if (!strcmp(tag, "cmd")) {
+            apr_status_t rv;
+
+            cgi_pfn_ps(ctx, tag_val, parsed_string, sizeof(parsed_string),
+                       SSI_EXPAND_LEAVE_NAME);
+
+            rv = include_cmd(ctx, f, bb, parsed_string);
+            if (rv != APR_SUCCESS) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "execution failure "
+                              "for parameter \"%s\" to tag exec in file %s",
+                              tag, r->filename);
+                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+                break;
+            }
         }
-        else {
-            while (1) {
-                cgi_pfn_gtv(ctx, &tag, &tag_val, 1);
-                if (tag_val == NULL) {
-                    if (tag == NULL) {
-                        return 0;
-                    }
-                    else {
-                        return 1;
-                    }
-                }
-                if (!strcmp(tag, "cmd")) {
-                    cgi_pfn_ps(r, ctx, tag_val, parsed_string,
-                               sizeof(parsed_string), 1);
-                    if (include_cmd(ctx, bb, parsed_string, r, f) == -1) {
-                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                    "execution failure for parameter \"%s\" "
-                                    "to tag exec in file %s", tag, r->filename);
-                        CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr,
-                                            *inserted_head);
-                    }
-                }
-                else if (!strcmp(tag, "cgi")) {
-                    apr_status_t retval = APR_SUCCESS;
+        else if (!strcmp(tag, "cgi")) {
+            apr_status_t rv;
 
-                    cgi_pfn_ps(r, ctx, tag_val, parsed_string,
-                               sizeof(parsed_string), 0);
+            cgi_pfn_ps(ctx, tag_val, parsed_string, sizeof(parsed_string),
+                       SSI_EXPAND_DROP_NAME);
 
-                    SPLIT_AND_PASS_PRETAG_BUCKETS(*bb, ctx, f->next, retval);
-                    if (retval != APR_SUCCESS) {
-                        return retval;
-                    }
-
-                    if (include_cgi(parsed_string, r, f->next, head_ptr,
-                                    inserted_head) == -1) {
-                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                      "invalid CGI ref \"%s\" in %s",
-                                      tag_val, file);
-                        CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr,
-                                            *inserted_head);
-                    }
-                }
-                else {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                                  "unknown parameter \"%s\" to tag exec in %s",
-                                  tag, file);
-                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr,
-                                        *inserted_head);
-                }
+            rv = include_cgi(ctx, f, bb, parsed_string);
+            if (rv != APR_SUCCESS) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "invalid CGI ref "
+                              "\"%s\" in %s", tag_val, file);
+                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+                break;
             }
         }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
+                          "\"%s\" to tag exec in %s", tag, file);
+            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
+            break;
+        }
     }
-    return 0;
+
+    return APR_SUCCESS;
 }
 
 
 /*============================================================================
  *============================================================================
  * This is the end of the cgi filter code moved from mod_include.

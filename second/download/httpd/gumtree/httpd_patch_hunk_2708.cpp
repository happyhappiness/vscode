                     if (rv != APR_SUCCESS) {
                         apr_brigade_destroy(pass_bb);
                         return rv;
                     }
                 }
                 else {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01371)
                                   "unknown directive \"%s\" in parsed doc %s",
                                   apr_pstrmemdup(r->pool, intern->directive,
                                                  intern->directive_len),
                                                  r->filename);
                     if (ctx->flags & SSI_FLAG_PRINTING) {
                         SSI_CREATE_ERROR_BUCKET(ctx, f, pass_bb);

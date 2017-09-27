         else {       /* *p == '$' */
             const char *newp = NULL, *ep, *key = NULL;
 
             if (*++p == '{') {
                 ep = ap_strchr_c(++p, '}');
                 if (!ep) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Missing '}' on "
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01331) "Missing '}' on "
                                   "variable \"%s\" in %s", p, r->filename);
                     break;
                 }
 
                 if (p < ep) {
                     key = apr_pstrmemdup(ctx->dpool, p, ep - p);

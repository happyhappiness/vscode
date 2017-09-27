 {
     ap_regex_t *compiled;
     backref_t *re = ctx->intern->re;
 
     compiled = ap_pregcomp(ctx->dpool, rexp, AP_REG_EXTENDED);
     if (!compiled) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, "unable to "
-                      "compile pattern \"%s\"", rexp);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02667)
+                      "unable to compile pattern \"%s\"", rexp);
         return -1;
     }
 
     if (!re) {
         re = ctx->intern->re = apr_palloc(ctx->pool, sizeof(*re));
     }

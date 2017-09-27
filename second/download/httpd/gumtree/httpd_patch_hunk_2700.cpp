 {
     request_rec *r = f->r;
 
     if (ctx->argc) {
         ap_log_rerror(APLOG_MARK,
                       (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
-                      0, r, "else directive does not take tags in %s",
+                      0, r, APLOGNO(01360)
+                      "else directive does not take tags in %s",
                       r->filename);
     }
 
     if (ctx->if_nesting_level) {
         return APR_SUCCESS;
     }

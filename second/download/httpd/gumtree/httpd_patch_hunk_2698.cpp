     request_rec *r = f->r;
     int expr_ret, was_error;
 
     if (ctx->argc != 1) {
         ap_log_rerror(APLOG_MARK,
                       (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
-                      0, r, (ctx->argc)
-                                ? "too many arguments for if element in %s"
-                                : "missing expr argument for if element in %s",
+                      0, r,
+                      (ctx->argc)
+                      ? APLOGNO(01356) "too many arguments for if element in %s"
+                      : APLOGNO(01357) "missing expr argument for if element in %s",
                       r->filename);
     }
 
     if (ctx->if_nesting_level) {
         return APR_SUCCESS;
     }

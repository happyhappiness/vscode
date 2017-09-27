     if (!ctx->argc) {
         SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
         return APR_SUCCESS;
     }
 
     if (ctx->flags & SSI_FLAG_NO_EXEC) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "exec used but not allowed "
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01271) "exec used but not allowed "
                       "in %s", r->filename);
         SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
         return APR_SUCCESS;
     }
 
     while (1) {

     ef_ctx_t *ctx = f->ctx;
     apr_status_t rv;
 
     if (!ctx) {
         if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
             ctx = f->ctx;
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01467)
                           "can't initialise output filter %s: %s",
                           f->frec->name,
                           (ctx->dc->onfail == 1) ? "removing" : "aborting");
             ap_remove_output_filter(f);
             if (ctx->dc->onfail == 1) {
                 return ap_pass_brigade(f->next, bb);

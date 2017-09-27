         ap_remove_output_filter(f);
         return ap_pass_brigade(f->next, bb);
     }
 
     rv = ef_unified_filter(f, bb);
     if (rv != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01468)
                       "ef_unified_filter() failed");
     }
 
     if ((rv = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(01469)
                       "ap_pass_brigade() failed");
     }
     return rv;
 }
 
-static int ef_input_filter(ap_filter_t *f, apr_bucket_brigade *bb,
-                           ap_input_mode_t mode, apr_read_type_e block,
-                           apr_off_t readbytes)
+static apr_status_t ef_input_filter(ap_filter_t *f, apr_bucket_brigade *bb,
+                                    ap_input_mode_t mode, apr_read_type_e block,
+                                    apr_off_t readbytes)
 {
     ef_ctx_t *ctx = f->ctx;
     apr_status_t rv;
 
     if (!ctx) {
         if ((rv = init_filter_instance(f)) != APR_SUCCESS) {
             ctx = f->ctx;
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01470)
                           "can't initialise input filter %s: %s",
                           f->frec->name,
                           (ctx->dc->onfail == 1) ? "removing" : "aborting");
             ap_remove_input_filter(f);
             if (ctx->dc->onfail == 1) {
                 return ap_get_brigade(f->next, bb, mode, block, readbytes);

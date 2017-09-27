 
     if (ret == APR_SUCCESS) {
         for (b = APR_BRIGADE_FIRST(bb); b != APR_BRIGADE_SENTINEL(bb); b = APR_BUCKET_NEXT(b)) {
           dumpit(f, b);
         }
     } else {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server,
+        ap_log_error(APLOG_MARK, ptr->loglevel, 0, c->base_server,
         "mod_dumpio: %s - %d", f->frec->name, ret) ;
     }
 
     return APR_SUCCESS ;
 }
 
 static int dumpio_output_filter (ap_filter_t *f, apr_bucket_brigade *bb)
 {
     apr_bucket *b;
     conn_rec *c = f->c;
+    dumpio_conf_t *ptr =
+    (dumpio_conf_t *) ap_get_module_config(c->base_server->module_config,
+                                           &dumpio_module);
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, c->base_server, "mod_dumpio: %s", f->frec->name) ;
+    ap_log_error(APLOG_MARK, ptr->loglevel, 0, c->base_server, "mod_dumpio: %s", f->frec->name) ;
 
     for (b = APR_BRIGADE_FIRST(bb); b != APR_BRIGADE_SENTINEL(bb); b = APR_BUCKET_NEXT(b)) {
         /*
          * If we ever see an EOS, make sure to FLUSH.
          */
         if (APR_BUCKET_IS_EOS(b)) {

                                             apr_bucket_brigade *in)
 {
     headers_conf *dirconf;
 
     dirconf = ap_get_module_config(f->r->per_dir_config,
                                     &headers_module);
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server, APLOGNO(01503)
                  "headers: ap_headers_error_filter()");
 
     /*
      * Add any header fields defined by "Header always" to r->err_headers_out.
      * Server-wide first, then per-directory to allow overriding.
      */

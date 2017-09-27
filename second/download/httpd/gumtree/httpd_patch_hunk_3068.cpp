             err = 0;
             location = apr_table_get(r->headers_out, conf->sendfile);
         }
         if (location) {
             scgi_request_config *req_conf = apr_palloc(r->pool,
                                                        sizeof(*req_conf));
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                          "proxy: " PROXY_FUNCTION ": Found %s: %s - "
-                          "preparing subrequest.",
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00861)
+                          "Found %s: %s - preparing subrequest.",
                           conf->sendfile, location);
 
             if (err) {
                 apr_table_unset(r->err_headers_out, conf->sendfile);
             }
             else {

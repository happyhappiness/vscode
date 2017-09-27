                                 AP_MODE_READBYTES, APR_BLOCK_READ,
                                 maxsize - AJP_HEADER_SZ);
 
         if (status != APR_SUCCESS) {
             /* We had a failure: Close connection to backend */
             conn->close++;
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, status, r->server,
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: ap_get_brigade failed");
             apr_brigade_destroy(input_brigade);
-            return ap_map_http_request_error(status, HTTP_BAD_REQUEST);
+            return HTTP_BAD_REQUEST;
         }
 
         /* have something */
         if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: APR_BUCKET_IS_EOS");

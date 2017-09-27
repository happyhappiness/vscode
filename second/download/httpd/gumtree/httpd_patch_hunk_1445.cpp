         }
         else {
             /* no way to know what type of error occurred */
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                           "default_handler: ap_pass_brigade returned %i",
                           status);
-            return HTTP_INTERNAL_SERVER_ERROR;
+            return AP_FILTER_ERROR;
         }
     }
     else {              /* unusual method (not GET or POST) */
         if (r->method_number == M_INVALID) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "Invalid method in request %s", r->the_request);

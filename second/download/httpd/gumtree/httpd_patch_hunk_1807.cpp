         }
         else {
             /* no way to know what type of error occurred */
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                           "default_handler: ap_pass_brigade returned %i",
                           status);
-            return AP_FILTER_ERROR;
+            return HTTP_INTERNAL_SERVER_ERROR;
         }
     }
     else {              /* unusual method (not GET or POST) */
         if (r->method_number == M_INVALID) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "Invalid method in request %s", r->the_request);
+            /* See if this looks like an undecrypted SSL handshake attempt.
+             * It's safe to look a couple bytes into the_request if it exists, as it's
+             * always allocated at least MIN_LINE_ALLOC (80) bytes.
+             */
+            if (r->the_request
+                && r->the_request[0] == 0x16                                
+                && (r->the_request[1] == 0x2 || r->the_request[1] == 0x3)) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "Invalid method in request %s - possible attempt to establish SSL connection on non-SSL port", r->the_request);
+            } else {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "Invalid method in request %s", r->the_request);
+            }
             return HTTP_NOT_IMPLEMENTED;
         }
 
         if (r->method_number == M_OPTIONS) {
             return ap_send_http_options(r);
         }

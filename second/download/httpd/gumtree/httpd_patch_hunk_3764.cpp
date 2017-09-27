         }
         else {
             /* no way to know what type of error occurred */
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00133)
                           "default_handler: ap_pass_brigade returned %i",
                           status);
-            return HTTP_INTERNAL_SERVER_ERROR;
+            return AP_FILTER_ERROR;
         }
     }
     else {              /* unusual method (not GET or POST) */
         if (r->method_number == M_INVALID) {
             /* See if this looks like an undecrypted SSL handshake attempt.
              * It's safe to look a couple bytes into the_request if it exists, as it's

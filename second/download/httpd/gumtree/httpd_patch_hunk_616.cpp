         } else {
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: header only");
         }
     }
 
+    /* See define of AP_MAX_INTERIM_RESPONSES for why */
+    if (received_continue > AP_MAX_INTERIM_RESPONSES) {
+        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
+                             apr_psprintf(p, 
+                             "Too many (%d) interim responses from origin server",
+                             received_continue));
+    }
+
     if ( conf->error_override ) {
         /* the code above this checks for 'OK' which is what the hook expects */
         if ( r->status == HTTP_OK )
             return OK;
         else  {
             /* clear r->status for override error, otherwise ErrorDocument

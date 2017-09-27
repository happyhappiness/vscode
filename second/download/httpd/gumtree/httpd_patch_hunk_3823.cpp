                            "hostname using Server Name Indication (SNI), "
                            "which is required to access this server.<br />\n");
             return HTTP_FORBIDDEN;
         }
     }
 #endif
-    SSL_set_app_data2(ssl, r);
+    modssl_set_app_data2(ssl, r);
 
     /*
      * Log information about incoming HTTPS requests
      */
     if (APLOGrinfo(r) && ap_is_initial_req(r)) {
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02034)

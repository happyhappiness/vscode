             if (status != OK) {
                 return HTTP_SERVICE_UNAVAILABLE;
             }
             readlen = ap_get_client_block(r, buf, AP_IOBUFSIZE);
         }
         if (readlen == -1) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "proxy: " PROXY_FUNCTION ": receiving request body "
-                          "failed");
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00859)
+                          "receiving request body failed");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
     }
 
     return OK;
 }

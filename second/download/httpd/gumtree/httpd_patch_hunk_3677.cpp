 
         (*starting_elem)++;
         i++;
     }
 
     if (rv != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      APLOGNO(02492) "ap_fcgi_encode_env: out of space "
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02492)
+                      "ap_fcgi_encode_env: out of space "
                       "encoding environment");
     }
 
     return rv;
 }

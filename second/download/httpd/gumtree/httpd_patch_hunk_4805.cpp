     if (rv) {
         ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01978)
                       "failed reading line from OCSP server");
         return NULL;
     }
 
-    if (len && line[len-1] != APR_ASCII_LF) {
+    if (len == 0) {
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(02321)
+                      "empty response from OCSP server");
+        return NULL;
+    }
+
+    if (line[len-1] != APR_ASCII_LF) {
         ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01979)
                       "response header line too long from OCSP server");
         return NULL;
     }
 
     line[len-1] = '\0';

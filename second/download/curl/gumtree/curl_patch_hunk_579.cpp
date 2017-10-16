                      tkt.length,
                      schedule, &key, DES_DECRYPT);
   }
   memset(key, 0, sizeof(key));
   memset(schedule, 0, sizeof(schedule));
   memset(passwd, 0, sizeof(passwd));
-  if(Curl_base64_encode(conn->data, (char *)tktcopy.dat, tktcopy.length, &p)
-     < 1) {
-    failf(conn->data, "Out of memory base64-encoding.");
+  result = Curl_base64_encode(conn->data, (char *)tktcopy.dat, tktcopy.length,
+                              &p, &base64_sz);
+  if(result) {
+    Curl_failf(conn->data, "base64-encoding: %s", curl_easy_strerror(result));
     krb4_set_command_prot(conn, save);
-    return CURLE_OUT_OF_MEMORY;
+    return result;
   }
   memset (tktcopy.dat, 0, tktcopy.length);
 
   result = Curl_ftpsendf(conn, "SITE KAUTH %s %s", name, p);
   free(p);
   if(result)

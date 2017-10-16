   len = Curl_base64_decode(p, (char *)adat.dat);
   if(len < 0) {
     Curl_failf(data, "Failed to decode base64 from server");
     return AUTH_ERROR;
   }
   adat.length = len;
-  ret = krb_rd_safe(adat.dat, adat.length, &d->key, 
-                    (struct sockaddr_in *)hisctladdr, 
+  ret = krb_rd_safe(adat.dat, adat.length, &d->key,
+                    (struct sockaddr_in *)hisctladdr,
                     (struct sockaddr_in *)myctladdr, &msg_data);
   if(ret) {
-    Curl_failf(data, "Error reading reply from server: %s", 
+    Curl_failf(data, "Error reading reply from server: %s",
                krb_get_err_text(ret));
     return AUTH_ERROR;
   }
   krb_get_int(msg_data.app_data, &cs, 4, 0);
   if(cs - checksum != 1) {
     Curl_failf(data, "Bad checksum returned from server");

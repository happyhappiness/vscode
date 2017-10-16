   p = strstr(data->state.buffer, "ADAT=");
   if(!p) {
     Curl_failf(data, "Remote host didn't send adat reply");
     return AUTH_ERROR;
   }
   p += 5;
-  len = Curl_base64_decode(p, (char *)adat.dat);
-  if(len < 0) {
+  len = Curl_base64_decode(p, &ptr);
+  if(len > sizeof(adat.dat)-1) {
+    free(ptr);
+    len=0;
+  }
+  if(!len || !ptr) {
     Curl_failf(data, "Failed to decode base64 from server");
     return AUTH_ERROR;
   }
+  memcpy((char *)adat.dat, ptr, len);
+  free(ptr);
   adat.length = len;
   ret = krb_rd_safe(adat.dat, adat.length, &d->key,
                     (struct sockaddr_in *)hisctladdr,
                     (struct sockaddr_in *)myctladdr, &msg_data);
   if(ret) {
     Curl_failf(data, "Error reading reply from server: %s",

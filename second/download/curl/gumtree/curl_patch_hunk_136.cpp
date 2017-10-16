     Curl_failf(conn->data, "Bad reply from server");
     Curl_set_command_prot(conn, save);
     return CURLE_FTP_WEIRD_SERVER_REPLY;
   }
 
   p += 2;
-  tmp = Curl_base64_decode(p, (char *)tkt.dat);
-  if(tmp < 0) {
+  tmp = Curl_base64_decode(p, &ptr);
+  if(tmp >= sizeof(tkt.dat)) {
+    free(ptr);
+    tmp=0;
+  }
+  if(!tmp || !ptr) {
     Curl_failf(conn->data, "Failed to decode base64 in reply.\n");
     Curl_set_command_prot(conn, save);
     return CURLE_FTP_WEIRD_SERVER_REPLY;
   }
+  memcpy((char *)tkt.dat, ptr, tmp);
+  free(ptr);
   tkt.length = tmp;
   tktcopy.length = tkt.length;
 
   p = strstr(conn->data->state.buffer, "P=");
   if(!p) {
     Curl_failf(conn->data, "Bad reply from server");

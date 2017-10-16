   ssize_t nread;
 	
   int save;
 
   save = Curl_set_command_prot(conn, prot_private);
 
-  Curl_ftpsendf(conn->firstsocket, conn,
-                "SITE KAUTH %s", conn->data->state.user);
+  if(Curl_ftpsendf(conn, "SITE KAUTH %s", conn->data->state.user))
+    return;
 
-  nread = Curl_GetFTPResponse(conn->firstsocket, conn->data->state.buffer,
+  nread = Curl_GetFTPResponse(conn->data->state.buffer,
                               conn, NULL);
   if(nread < 0)
     return /*CURLE_OPERATION_TIMEOUTED*/;
 
-  if(/*ret != CONTINUE*/conn->data->state.buffer[0] != '3'){
+  if(conn->data->state.buffer[0] != '3'){
     Curl_set_command_prot(conn, save);
-    /*code = -1;***/
     return;
   }
 
   p = strstr(conn->data->state.buffer, "T=");
   if(!p) {
-    printf("Bad reply from server.\n");
+    Curl_failf(conn->data, "Bad reply from server");
     Curl_set_command_prot(conn, save);
     return;
   }
 
   p += 2;
   tmp = Curl_base64_decode(p, &tkt.dat);
   if(tmp < 0) {
-    printf("Failed to decode base64 in reply.\n");
+    Curl_failf(conn->data, "Failed to decode base64 in reply.\n");
     Curl_set_command_prot(conn, save);
     return;
   }
   tkt.length = tmp;
   tktcopy.length = tkt.length;
     
   p = strstr(conn->data->state.buffer, "P=");
   if(!p) {
-    printf("Bad reply from server.\n");
+    Curl_failf(conn->data, "Bad reply from server");
     Curl_set_command_prot(conn, save);
     return;
   }
   name = p + 2;
   for(; *p && *p != ' ' && *p != '\r' && *p != '\n'; p++);
   *p = 0;

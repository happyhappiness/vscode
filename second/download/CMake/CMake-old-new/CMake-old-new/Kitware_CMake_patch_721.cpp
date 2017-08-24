@@ -202,6 +202,7 @@ krb4_auth(void *app_data, struct connectdata *conn)
   ssize_t nread;
   int l = sizeof(conn->local_addr);
   struct SessionHandle *data = conn->data;
+  CURLcode result;
 
   if(getsockname(conn->firstsocket,
                  (struct sockaddr *)LOCAL_ADDR, &l) < 0)
@@ -246,13 +247,15 @@ krb4_auth(void *app_data, struct connectdata *conn)
     return AUTH_CONTINUE;
   }
 
-  if(Curl_ftpsendf(conn, "ADAT %s", p))
+  result = Curl_ftpsendf(conn, "ADAT %s", p);
+
+  free(p);
+
+  if(result)
     return -2;
 
-  nread = Curl_GetFTPResponse(data->state.buffer, conn, NULL);
-  if(nread < 0)
+  if(Curl_GetFTPResponse(&nread, conn, NULL))
     return -1;
-  free(p);
 
   if(data->state.buffer[0] != '2'){
     Curl_failf(data, "Server didn't accept auth data");
@@ -299,7 +302,7 @@ struct Curl_sec_client_mech Curl_krb4_client_mech = {
     krb4_decode
 };
 
-void Curl_krb_kauth(struct connectdata *conn)
+CURLcode Curl_krb_kauth(struct connectdata *conn)
 {
   des_cblock key;
   des_key_schedule schedule;
@@ -309,18 +312,19 @@ void Curl_krb_kauth(struct connectdata *conn)
   char passwd[100];
   int tmp;
   ssize_t nread;
-        
   int save;
+  CURLcode result;
 
   save = Curl_set_command_prot(conn, prot_private);
 
-  if(Curl_ftpsendf(conn, "SITE KAUTH %s", conn->data->state.user))
-    return;
+  result = Curl_ftpsendf(conn, "SITE KAUTH %s", conn->data->state.user);
+
+  if(result)
+    return result;
 
-  nread = Curl_GetFTPResponse(conn->data->state.buffer,
-                              conn, NULL);
-  if(nread < 0)
-    return /*CURLE_OPERATION_TIMEOUTED*/;
+  result = Curl_GetFTPResponse(&nread, conn, NULL);
+  if(result)
+    return result;
 
   if(conn->data->state.buffer[0] != '3'){
     Curl_set_command_prot(conn, save);
@@ -331,15 +335,15 @@ void Curl_krb_kauth(struct connectdata *conn)
   if(!p) {
     Curl_failf(conn->data, "Bad reply from server");
     Curl_set_command_prot(conn, save);
-    return;
+    return CURLE_FTP_WEIRD_SERVER_REPLY;
   }
 
   p += 2;
   tmp = Curl_base64_decode(p, &tkt.dat);
   if(tmp < 0) {
     Curl_failf(conn->data, "Failed to decode base64 in reply.\n");
     Curl_set_command_prot(conn, save);
-    return;
+    return CURLE_FTP_WEIRD_SERVER_REPLY;
   }
   tkt.length = tmp;
   tktcopy.length = tkt.length;
@@ -348,7 +352,7 @@ void Curl_krb_kauth(struct connectdata *conn)
   if(!p) {
     Curl_failf(conn->data, "Bad reply from server");
     Curl_set_command_prot(conn, save);
-    return;
+    return CURLE_FTP_WEIRD_SERVER_REPLY;
   }
   name = p + 2;
   for(; *p && *p != ' ' && *p != '\r' && *p != '\n'; p++);
@@ -376,19 +380,21 @@ void Curl_krb_kauth(struct connectdata *conn)
   if(Curl_base64_encode(tktcopy.dat, tktcopy.length, &p) < 0) {
     failf(conn->data, "Out of memory base64-encoding.");
     Curl_set_command_prot(conn, save);
-    return;
+    return CURLE_OUT_OF_MEMORY;
   }
   memset (tktcopy.dat, 0, tktcopy.length);
 
-  if(Curl_ftpsendf(conn, "SITE KAUTH %s %s", name, p))
-    return;
-
-  nread = Curl_GetFTPResponse(conn->data->state.buffer,
-                              conn, NULL);
-  if(nread < 0)
-    return /*CURLE_OPERATION_TIMEOUTED*/;
+  result = Curl_ftpsendf(conn, "SITE KAUTH %s %s", name, p);
   free(p);
+  if(result)
+    return result;
+
+  result = Curl_GetFTPResponse(&nread, conn, NULL);
+  if(result)
+    return result;
   Curl_set_command_prot(conn, save);
+
+  return CURLE_OK;
 }
 
 #endif /* KRB4 */
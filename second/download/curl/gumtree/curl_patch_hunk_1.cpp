 
   if(Curl_base64_encode(adat.dat, adat.length, &p) < 0) {
     Curl_failf(data, "Out of memory base64-encoding");
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
     return AUTH_ERROR;
   }
 

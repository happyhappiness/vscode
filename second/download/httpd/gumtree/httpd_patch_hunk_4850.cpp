                      sizeof(struct tlsserveropts),
                      NULL,
                      0,
                      NULL,
                      NULL,
                      NULL);
-    if(SOCKET_ERROR == rcode) {
+    if (SOCKET_ERROR == rcode) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02128)
                      "Error: %d with WSAIoctl(SO_TLS_SET_SERVER)", WSAGetLastError());
         goto ERR;
     }
 
 ERR:

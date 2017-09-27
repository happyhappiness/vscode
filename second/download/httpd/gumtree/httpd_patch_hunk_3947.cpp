     memset((char *)&sWS2Opts, 0, sizeof(struct tlsserveropts));
     memset((char *)&sNWTLSOpts, 0, sizeof(struct nwtlsopts));
 
     ulFlag = SO_TLS_ENABLE;
     rcode = WSAIoctl(socketHnd, SO_TLS_SET_FLAGS, &ulFlag,
                      sizeof(unsigned long), NULL, 0, NULL, NULL, NULL);
-    if(rcode) {
+    if (rcode) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02126)
                      "Error: %d with WSAIoctl(SO_TLS_SET_FLAGS, SO_TLS_ENABLE)",
                      WSAGetLastError());
         goto ERR;
     }
 

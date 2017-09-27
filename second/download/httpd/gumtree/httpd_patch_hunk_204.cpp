 
 int convert_secure_socket(conn_rec *c, apr_socket_t *csd)
 {
 	int rcode;
 	struct tlsclientopts sWS2Opts;
 	struct nwtlsopts sNWTLSOpts;
-	unsigned long ulFlags;
+   	struct sslserveropts opts;
+    unsigned long ulFlags;
     SOCKET sock;
+    unicode_t keyFileName[60];
 
     apr_os_sock_get(&sock, csd);
 
     /* zero out buffers */
 	memset((char *)&sWS2Opts, 0, sizeof(struct tlsclientopts));
 	memset((char *)&sNWTLSOpts, 0, sizeof(struct nwtlsopts));
 
     /* turn on ssl for the socket */
-	ulFlags = SO_TLS_ENABLE;
+	ulFlags = (numcerts ? SO_TLS_ENABLE : SO_TLS_ENABLE | SO_TLS_BLIND_ACCEPT);
 	rcode = WSAIoctl(sock, SO_TLS_SET_FLAGS, &ulFlags, sizeof(unsigned long),
                      NULL, 0, NULL, NULL, NULL);
 	if (SOCKET_ERROR == rcode)
 	{
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                      "Error: %d with ioctlsocket(flag SO_TLS_ENABLE)", WSAGetLastError());

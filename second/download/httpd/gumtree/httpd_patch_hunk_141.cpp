     opts.sidtimeout = 0;
     opts.sidentries = 0;
     opts.siddir = NULL;
 
     if (WSAIoctl(s, SO_SSL_SET_SERVER, (char *)&opts, sizeof(opts),
         NULL, 0, NULL, NULL, NULL) != 0) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf,
                      "make_secure_socket: for %s, WSAIoctl: "
                      "(SO_SSL_SET_SERVER)", addr);
         return -1;
     }
 
     if (mutual) {
-        optParam = 0x07;               // SO_SSL_AUTH_CLIENT
+        optParam = 0x07;  // SO_SSL_AUTH_CLIENT
 
         if(WSAIoctl(s, SO_SSL_SET_FLAGS, (char*)&optParam,
             sizeof(optParam), NULL, 0, NULL, NULL, NULL)) {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
+            ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf,
                          "make_secure_socket: for %s, WSAIoctl: "
                          "(SO_SSL_SET_FLAGS)", addr);
             return -1;
         }
     }
 
+    optParam = SO_TLS_UNCLEAN_SHUTDOWN;
+    WSAIoctl(s, SO_SSL_SET_FLAGS, (char *)&optParam, sizeof(optParam), 
+             NULL, 0, NULL, NULL, NULL);
+
     return s;
 }
 
+int convert_secure_socket(conn_rec *c, apr_socket_t *csd)
+{
+	int rcode;
+	struct tlsclientopts sWS2Opts;
+	struct nwtlsopts sNWTLSOpts;
+   	struct sslserveropts opts;
+    unsigned long ulFlags;
+    SOCKET sock;
+    unicode_t keyFileName[60];
+
+    apr_os_sock_get(&sock, csd);
+
+    /* zero out buffers */
+	memset((char *)&sWS2Opts, 0, sizeof(struct tlsclientopts));
+	memset((char *)&sNWTLSOpts, 0, sizeof(struct nwtlsopts));
+
+    /* turn on ssl for the socket */
+	ulFlags = (numcerts ? SO_TLS_ENABLE : SO_TLS_ENABLE | SO_TLS_BLIND_ACCEPT);
+	rcode = WSAIoctl(sock, SO_TLS_SET_FLAGS, &ulFlags, sizeof(unsigned long),
+                     NULL, 0, NULL, NULL, NULL);
+	if (SOCKET_ERROR == rcode)
+	{
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
+                     "Error: %d with ioctlsocket(flag SO_TLS_ENABLE)", WSAGetLastError());
+		return rcode;
+	}
+
+    ulFlags = SO_TLS_UNCLEAN_SHUTDOWN;
+	WSAIoctl(sock, SO_TLS_SET_FLAGS, &ulFlags, sizeof(unsigned long),
+                     NULL, 0, NULL, NULL, NULL);
+
+    /* setup the socket for SSL */
+    memset (&sWS2Opts, 0, sizeof(sWS2Opts));
+    memset (&sNWTLSOpts, 0, sizeof(sNWTLSOpts));
+    sWS2Opts.options = &sNWTLSOpts;
+
+    if (numcerts) {
+    	sNWTLSOpts.walletProvider 		= WAL_PROV_DER;	//the wallet provider defined in wdefs.h
+    	sNWTLSOpts.TrustedRootList 		= certarray;	//array of certs in UNICODE format
+    	sNWTLSOpts.numElementsInTRList 	= numcerts;     //number of certs in TRList
+    }
+    else {
+        /* setup the socket for SSL */
+    	unicpy(keyFileName, L"SSL CertificateIP");
+    	sWS2Opts.wallet = keyFileName;    /* no client certificate */
+    	sWS2Opts.walletlen = unilen(keyFileName);
+    
+    	sNWTLSOpts.walletProvider 		= WAL_PROV_KMO;	//the wallet provider defined in wdefs.h
+    }
+
+    /* make the IOCTL call */
+    rcode = WSAIoctl(sock, SO_TLS_SET_CLIENT, &sWS2Opts,
+                     sizeof(struct tlsclientopts), NULL, 0, NULL,
+                     NULL, NULL);
+
+    /* make sure that it was successfull */
+	if(SOCKET_ERROR == rcode ){
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
+                     "Error: %d with ioctl (SO_TLS_SET_CLIENT)", WSAGetLastError());
+	}		
+	return rcode;
+}
+
 static const char *set_secure_listener(cmd_parms *cmd, void *dummy, 
                                        const char *ips, const char* key, 
                                        const char* mutual)
 {
     NWSSLSrvConfigRec* sc = get_nwssl_cfg(cmd->server);
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

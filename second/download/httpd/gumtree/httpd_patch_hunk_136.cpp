         }
     }
 
     return s;
 }
 
+int convert_secure_socket(conn_rec *c, apr_socket_t *csd)
+{
+	int rcode;
+	struct tlsclientopts sWS2Opts;
+	struct nwtlsopts sNWTLSOpts;
+	unsigned long ulFlags;
+    SOCKET sock;
+
+    apr_os_sock_get(&sock, csd);
+
+    /* zero out buffers */
+	memset((char *)&sWS2Opts, 0, sizeof(struct tlsclientopts));
+	memset((char *)&sNWTLSOpts, 0, sizeof(struct nwtlsopts));
+
+    /* turn on ssl for the socket */
+	ulFlags = SO_TLS_ENABLE;
+	rcode = WSAIoctl(sock, SO_TLS_SET_FLAGS, &ulFlags, sizeof(unsigned long),
+                     NULL, 0, NULL, NULL, NULL);
+	if (SOCKET_ERROR == rcode)
+	{
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
+                     "Error: %d with ioctlsocket(flag SO_TLS_ENABLE)", WSAGetLastError());
+		return rcode;
+	}
+
+
+    /* setup the socket for SSL */
+	sWS2Opts.wallet = NULL;    /* no client certificate */
+	sWS2Opts.walletlen = 0;
+	sWS2Opts.sidtimeout = 0;
+	sWS2Opts.sidentries = 0;
+	sWS2Opts.siddir = NULL;
+	sWS2Opts.options = &sNWTLSOpts;
+
+	sNWTLSOpts.walletProvider 		= WAL_PROV_DER;	//the wallet provider defined in wdefs.h
+	sNWTLSOpts.TrustedRootList 		= certarray;	//array of certs in UNICODE format
+	sNWTLSOpts.numElementsInTRList 	= numcerts;     //number of certs in TRList
+	sNWTLSOpts.keysList 			= NULL;
+	sNWTLSOpts.numElementsInKeyList = 0;
+	sNWTLSOpts.reservedforfutureuse = NULL;
+	sNWTLSOpts.reservedforfutureCRL = NULL;
+	sNWTLSOpts.reservedforfutureCRLLen = 0;
+	sNWTLSOpts.reserved1			= NULL;
+	sNWTLSOpts.reserved2			= NULL;
+	sNWTLSOpts.reserved3			= NULL;
+	
+	
+    /* make the IOCTL call */
+	rcode = WSAIoctl(sock, SO_TLS_SET_CLIENT, &sWS2Opts,
+	  			     sizeof(struct tlsclientopts), NULL, 0, NULL,
+				     NULL, NULL);
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

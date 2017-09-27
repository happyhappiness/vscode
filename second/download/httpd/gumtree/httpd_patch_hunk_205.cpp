 	{
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                      "Error: %d with ioctlsocket(flag SO_TLS_ENABLE)", WSAGetLastError());
 		return rcode;
 	}
 
-
     /* setup the socket for SSL */
-	sWS2Opts.wallet = NULL;    /* no client certificate */
-	sWS2Opts.walletlen = 0;
-	sWS2Opts.sidtimeout = 0;
-	sWS2Opts.sidentries = 0;
-	sWS2Opts.siddir = NULL;
-	sWS2Opts.options = &sNWTLSOpts;
+    memset (&sWS2Opts, 0, sizeof(sWS2Opts));
+    memset (&sNWTLSOpts, 0, sizeof(sNWTLSOpts));
+    sWS2Opts.options = &sNWTLSOpts;
 
+    if (numcerts) {
 	sNWTLSOpts.walletProvider 		= WAL_PROV_DER;	//the wallet provider defined in wdefs.h
 	sNWTLSOpts.TrustedRootList 		= certarray;	//array of certs in UNICODE format
 	sNWTLSOpts.numElementsInTRList 	= numcerts;     //number of certs in TRList
-	sNWTLSOpts.keysList 			= NULL;
-	sNWTLSOpts.numElementsInKeyList = 0;
-	sNWTLSOpts.reservedforfutureuse = NULL;
-	sNWTLSOpts.reservedforfutureCRL = NULL;
-	sNWTLSOpts.reservedforfutureCRLLen = 0;
-	sNWTLSOpts.reserved1			= NULL;
-	sNWTLSOpts.reserved2			= NULL;
-	sNWTLSOpts.reserved3			= NULL;
-	
-	
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
     /* make the IOCTL call */
-	rcode = WSAIoctl(sock, SO_TLS_SET_CLIENT, &sWS2Opts,
-	  			     sizeof(struct tlsclientopts), NULL, 0, NULL,
-				     NULL, NULL);
-	
+    rcode = WSAIoctl(sock, SO_TLS_SET_CLIENT, &sWS2Opts,
+                     sizeof(struct tlsclientopts), NULL, 0, NULL,
+                     NULL, NULL);
+
     /* make sure that it was successfull */
 	if(SOCKET_ERROR == rcode ){
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                      "Error: %d with ioctl (SO_TLS_SET_CLIENT)", WSAGetLastError());
 	}		
 	return rcode;

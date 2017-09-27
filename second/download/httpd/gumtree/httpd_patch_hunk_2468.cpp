 
 
     ulFlag = SO_TLS_ENABLE;
     rcode = WSAIoctl(socketHnd, SO_TLS_SET_FLAGS, &ulFlag, sizeof(unsigned long), NULL, 0, NULL, NULL, NULL);
     if(rcode)
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02126)
                      "Error: %d with WSAIoctl(SO_TLS_SET_FLAGS, SO_TLS_ENABLE)", WSAGetLastError());
         goto ERR;
     }
 
 
     ulFlag = SO_TLS_SERVER;
     rcode = WSAIoctl(socketHnd, SO_TLS_SET_FLAGS, &ulFlag, sizeof(unsigned long),NULL, 0, NULL, NULL, NULL);
 
     if(rcode)
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02127)
                      "Error: %d with WSAIoctl(SO_TLS_SET_FLAGS, SO_TLS_SERVER)", WSAGetLastError());
         goto ERR;
     }
 
     loc2uni(UNI_LOCAL_DEFAULT, SASKey, key, 0, 0);
 
-    //setup the tlsserveropts struct
+    /* setup the tlsserveropts struct */
     sWS2Opts.wallet = SASKey;
     sWS2Opts.walletlen = unilen(SASKey);
     sWS2Opts.sidtimeout = 0;
     sWS2Opts.sidentries = 0;
     sWS2Opts.siddir = NULL;
     sWS2Opts.options = &sNWTLSOpts;
 
-    //setup the nwtlsopts structure
+    /* setup the nwtlsopts structure */
 
     sNWTLSOpts.walletProvider               = WAL_PROV_KMO;
     sNWTLSOpts.keysList                     = NULL;
     sNWTLSOpts.numElementsInKeyList         = 0;
     sNWTLSOpts.reservedforfutureuse         = NULL;
     sNWTLSOpts.reservedforfutureCRL         = NULL;

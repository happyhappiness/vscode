     SecureProtoInfo.iSecurityScheme = SECURITY_PROTOCOL_SSL;
 
     s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,
             (LPWSAPROTOCOL_INFO)&SecureProtoInfo, 0, 0);
             
     if (s == INVALID_SOCKET) {
-        errno = WSAGetLastError();
-        ap_log_error(APLOG_MARK, APLOG_CRIT, errno, server_conf,
-            "make_secure_socket: failed to get a socket for %s", addr);
+        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
+                     "make_secure_socket: failed to get a socket for %s", 
+                     addr);
         return -1;
     }
         
     if (!mutual) {
         optParam = SO_SSL_ENABLE | SO_SSL_SERVER;
 		    
         if (WSAIoctl(s, SO_SSL_SET_FLAGS, (char *)&optParam,
             sizeof(optParam), NULL, 0, NULL, NULL, NULL)) {
-            errno = WSAGetLastError();
-            ap_log_error(APLOG_MARK, APLOG_CRIT, errno, server_conf,
-                "make_secure_socket: for %s, WSAIoctl: (SO_SSL_SET_FLAGS)", addr);
+            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
+                         "make_secure_socket: for %s, WSAIoctl: "
+                         "(SO_SSL_SET_FLAGS)", addr);
             return -1;
         }
     }
 
     opts.cert = key;
     opts.certlen = strlen(key);
     opts.sidtimeout = 0;
     opts.sidentries = 0;
     opts.siddir = NULL;
 
     if (WSAIoctl(s, SO_SSL_SET_SERVER, (char *)&opts, sizeof(opts),
         NULL, 0, NULL, NULL, NULL) != 0) {
-        errno = WSAGetLastError();
-        ap_log_error(APLOG_MARK, APLOG_CRIT, errno, server_conf,
-            "make_secure_socket: for %s, WSAIoctl: (SO_SSL_SET_SERVER)", addr);
+        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
+                     "make_secure_socket: for %s, WSAIoctl: "
+                     "(SO_SSL_SET_SERVER)", addr);
         return -1;
     }
 
     if (mutual) {
         optParam = 0x07;               // SO_SSL_AUTH_CLIENT
 
         if(WSAIoctl(s, SO_SSL_SET_FLAGS, (char*)&optParam,
             sizeof(optParam), NULL, 0, NULL, NULL, NULL)) {
-            errno = WSAGetLastError();
-            ap_log_error( APLOG_MARK, APLOG_CRIT, errno, server_conf,
-                "make_secure_socket: for %s, WSAIoctl: (SO_SSL_SET_FLAGS)", addr );
+            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
+                         "make_secure_socket: for %s, WSAIoctl: "
+                         "(SO_SSL_SET_FLAGS)", addr);
             return -1;
         }
     }
 
     return s;
 }

     SecureProtoInfo.iSecurityScheme = SECURITY_PROTOCOL_SSL;
 
     s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,
             (LPWSAPROTOCOL_INFO)&SecureProtoInfo, 0, 0);
             
     if (s == INVALID_SOCKET) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
+        ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf,
                      "make_secure_socket: failed to get a socket for %s", 
                      addr);
         return -1;
     }
         
     if (!mutual) {
         optParam = SO_SSL_ENABLE | SO_SSL_SERVER;
 		    
         if (WSAIoctl(s, SO_SSL_SET_FLAGS, (char *)&optParam,
             sizeof(optParam), NULL, 0, NULL, NULL, NULL)) {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
+            ap_log_error(APLOG_MARK, APLOG_CRIT, WSAGetLastError(), sconf,
                          "make_secure_socket: for %s, WSAIoctl: "
                          "(SO_SSL_SET_FLAGS)", addr);
             return -1;
         }
     }
 

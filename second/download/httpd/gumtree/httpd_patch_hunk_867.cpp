     }
 
 #if APR_TCP_NODELAY_INHERITED
     ap_sock_disable_nagle(s);
 #endif
 
-    if ((stat = apr_bind(s, server->bind_addr)) != APR_SUCCESS) {
+    if ((stat = apr_socket_bind(s, server->bind_addr)) != APR_SUCCESS) {
         ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, stat, p,
                       "make_sock: could not bind to address %pI",
                       server->bind_addr);
         apr_socket_close(s);
         return stat;
     }
 
-    if ((stat = apr_listen(s, ap_listenbacklog)) != APR_SUCCESS) {
+    if ((stat = apr_socket_listen(s, ap_listenbacklog)) != APR_SUCCESS) {
         ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, stat, p,
                       "make_sock: unable to listen for connections "
                       "on address %pI",
                       server->bind_addr);
         apr_socket_close(s);
         return stat;

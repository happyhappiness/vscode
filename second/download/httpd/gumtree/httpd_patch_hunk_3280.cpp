      *
      * If no size is specified, use the kernel default.
      */
     if (send_buffer_size) {
         stat = apr_socket_opt_set(s, APR_SO_SNDBUF,  send_buffer_size);
         if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
-            ap_log_perror(APLOG_MARK, APLOG_WARNING, stat, p,
+            ap_log_perror(APLOG_MARK, APLOG_WARNING, stat, p, APLOGNO(00070)
                           "make_sock: failed to set SendBufferSize for "
                           "address %pI, using default",
                           server->bind_addr);
             /* not a fatal error */
         }
     }
     if (receive_buffer_size) {
         stat = apr_socket_opt_set(s, APR_SO_RCVBUF, receive_buffer_size);
         if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
-            ap_log_perror(APLOG_MARK, APLOG_WARNING, stat, p,
+            ap_log_perror(APLOG_MARK, APLOG_WARNING, stat, p, APLOGNO(00071)
                           "make_sock: failed to set ReceiveBufferSize for "
                           "address %pI, using default",
                           server->bind_addr);
             /* not a fatal error */
         }
     }
 
 #if APR_TCP_NODELAY_INHERITED
     ap_sock_disable_nagle(s);
 #endif
 
     if ((stat = apr_socket_bind(s, server->bind_addr)) != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, stat, p,
+        ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, stat, p, APLOGNO(00072)
                       "make_sock: could not bind to address %pI",
                       server->bind_addr);
         apr_socket_close(s);
         return stat;
     }
 
     if ((stat = apr_socket_listen(s, ap_listenbacklog)) != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, stat, p,
+        ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_ERR, stat, p, APLOGNO(00073)
                       "make_sock: unable to listen for connections "
                       "on address %pI",
                       server->bind_addr);
         apr_socket_close(s);
         return stat;
     }

                           "make_sock: failed to set SendBufferSize for "
                           "address %pI, using default",
                           server->bind_addr);
             /* not a fatal error */
         }
     }
+    if (receive_buffer_size) {
+        stat = apr_socket_opt_set(s, APR_SO_RCVBUF, receive_buffer_size);
+        if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
+            ap_log_perror(APLOG_MARK, APLOG_WARNING, stat, p,
+                          "make_sock: failed to set ReceiveBufferSize for "
+                          "address %pI, using default",
+                          server->bind_addr);
+            /* not a fatal error */
+        }
+    }
 
 #if APR_TCP_NODELAY_INHERITED
     ap_sock_disable_nagle(s);
 #endif
 
     if ((stat = apr_bind(s, server->bind_addr)) != APR_SUCCESS) {

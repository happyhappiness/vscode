     }
 
 #if APR_TCP_NODELAY_INHERITED
     ap_sock_disable_nagle(s);
 #endif
 
+#if defined(SO_REUSEPORT)
+    if (ap_have_so_reuseport) {
+        int thesock;
+        apr_os_sock_get(&thesock, s);
+        if (setsockopt(thesock, SOL_SOCKET, SO_REUSEPORT,
+                       (void *)&one, sizeof(int)) < 0) {
+            stat = apr_get_netos_error();
+            ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p, APLOGNO(02638)
+                          "make_sock: for address %pI, apr_socket_opt_set: "
+                          "(SO_REUSEPORT)",
+                          server->bind_addr);
+            apr_socket_close(s);
+            return stat;
+        }
+    }
+#endif
+
     if ((stat = apr_socket_bind(s, server->bind_addr)) != APR_SUCCESS) {
         ap_log_perror(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, stat, p, APLOGNO(00072)
                       "make_sock: could not bind to address %pI",
                       server->bind_addr);
         apr_socket_close(s);
         return stat;

                       "make_sock: for address %pI, apr_socket_opt_set: (SO_KEEPALIVE)",
                       server->bind_addr);
         apr_socket_close(s);
         return stat;
     }
 
+#if APR_HAVE_IPV6
+    if (server->bind_addr->family == APR_INET6) {
+        stat = apr_socket_opt_set(s, APR_IPV6_V6ONLY, v6only_setting);
+        if (stat != APR_SUCCESS && stat != APR_ENOTIMPL) {
+            ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p,
+                          "make_sock: for address %pI, apr_socket_opt_set: "
+                          "(IPV6_V6ONLY)",
+                          server->bind_addr);
+            apr_socket_close(s);
+            return stat;
+        }
+    }
+#endif
+
     /*
      * To send data over high bandwidth-delay connections at full
      * speed we must force the TCP window to open wide enough to keep the
      * pipe full.  The default window size on many systems
      * is only 4kB.  Cross-country WAN connections of 100ms
      * at 1Mb/s are not impossible for well connected sites.

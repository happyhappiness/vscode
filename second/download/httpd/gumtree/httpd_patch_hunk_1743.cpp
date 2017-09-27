 
         apr_sockaddr_ip_get(&addr, s->addrs->host_addr);
         key = apr_psprintf(p, "%s:%u", addr, s->addrs->host_port);
         klen = strlen(key);
 
         if ((ps = (server_rec *)apr_hash_get(table, key, klen))) {
+            ap_log_error(APLOG_MARK, 
+#ifdef OPENSSL_NO_TLSEXT
+                         APLOG_WARNING, 
+#else
+                         APLOG_DEBUG, 
+#endif
+                         0,
+                         base_server,
 #ifdef OPENSSL_NO_TLSEXT
-            int level = APLOG_WARNING;
-            const char *problem = "conflict";
+                         "Init: SSL server IP/port conflict: "
 #else
-            int level = APLOG_DEBUG;
-            const char *problem = "overlap";
+                         "Init: SSL server IP/port overlap: "
 #endif
-            ap_log_error(APLOG_MARK, level, 0, base_server,
-                         "Init: SSL server IP/port %s: "
                          "%s (%s:%d) vs. %s (%s:%d)",
-                         problem, ssl_util_vhostid(p, s),
+                         ssl_util_vhostid(p, s),
                          (s->defn_name ? s->defn_name : "unknown"),
                          s->defn_line_number,
                          ssl_util_vhostid(p, ps),
                          (ps->defn_name ? ps->defn_name : "unknown"),
                          ps->defn_line_number);
             conflict = TRUE;

     void *sconf = s->module_config;
     proxy_server_conf *conf =
         (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
 
     if (conn->sock) {
         if (!(connected = is_socket_connected(conn->sock))) {
+            /* This clears conn->scpool (and associated data), so backup and
+             * restore any ssl_hostname for this connection set earlier by
+             * ap_proxy_determine_connection().
+             */
+            char ssl_hostname[PROXY_WORKER_RFC1035_NAME_SIZE];
+            if (!conn->ssl_hostname ||
+                    conn->ssl_hostname[apr_cpystrn(ssl_hostname,
+                                                   conn->ssl_hostname,
+                                                   sizeof ssl_hostname) -
+                                       ssl_hostname]) {
+                ssl_hostname[0] = '\0';
+            }
+
             socket_cleanup(conn);
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                          "proxy: %s: backend socket is disconnected.",
                          proxy_function);
+
+            if (ssl_hostname[0]) {
+                conn->ssl_hostname = apr_pstrdup(conn->scpool, ssl_hostname);
+            }
         }
     }
     while (backend_addr && !connected) {
         if ((rv = apr_socket_create(&newsock, backend_addr->family,
                                 SOCK_STREAM, APR_PROTO_TCP,
                                 conn->scpool)) != APR_SUCCESS) {

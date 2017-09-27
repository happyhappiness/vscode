     if (APR_STATUS_IS_EOF(socket_status) || 
         APR_STATUS_IS_ECONNRESET(socket_status))
         return 0;
     else
         return 1;
 }
+#endif /* USE_ALTERNATE_IS_CONNECTED */
 
 PROXY_DECLARE(int) ap_proxy_connect_backend(const char *proxy_function,
                                             proxy_conn_rec *conn,
                                             proxy_worker *worker,
                                             server_rec *s)
 {
     apr_status_t rv;
     int connected = 0;
     int loglevel;
     apr_sockaddr_t *backend_addr = conn->addr;
     apr_socket_t *newsock;
+    void *sconf = s->module_config;
+    proxy_server_conf *conf =
+        (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
 
     if (conn->sock) {
         /*
          * This increases the connection pool size
          * but the number of dropped connections is
          * relatively small compared to connection lifetime
          */
         if (!(connected = is_socket_connected(conn->sock))) {
             apr_socket_close(conn->sock);
             conn->sock = NULL;
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                         "proxy: %s: backend socket is disconnected.",
+                         proxy_function);
         }
     }
     while (backend_addr && !connected) {
         if ((rv = apr_socket_create(&newsock, backend_addr->family,
                                 SOCK_STREAM, APR_PROTO_TCP,
                                 conn->pool)) != APR_SUCCESS) {

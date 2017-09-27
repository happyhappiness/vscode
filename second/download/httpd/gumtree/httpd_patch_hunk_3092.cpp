     if (!conn->connection) {
         /*
          * the peer reset the connection already; ap_run_create_connection()
          * closed the socket
          */
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
-                     s, "proxy: %s: an error occurred creating a "
+                     s, APLOGNO(00960) "%s: an error occurred creating a "
                      "new connection to %pI (%s)", proxy_function,
                      backend_addr, conn->hostname);
         /* XXX: Will be closed when proxy_conn is closed */
         socket_cleanup(conn);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     /* For ssl connection to backend */
     if (conn->is_ssl) {
         if (!ap_proxy_ssl_enable(conn->connection)) {
             ap_log_error(APLOG_MARK, APLOG_ERR, 0,
-                         s, "proxy: %s: failed to enable ssl support "
+                         s, APLOGNO(00961) "%s: failed to enable ssl support "
                          "for %pI (%s)", proxy_function,
                          backend_addr, conn->hostname);
             return HTTP_INTERNAL_SERVER_ERROR;
         }
     }
     else {
         /* TODO: See if this will break FTP */
         ap_proxy_ssl_disable(conn->connection);
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                 "proxy: %s: connection complete to %pI (%s)",
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00962)
+                 "%s: connection complete to %pI (%s)",
                  proxy_function, backend_addr, conn->hostname);
 
     /*
      * save the timeout of the socket because core_pre_connection
      * will set it to base_server->timeout
      * (core TimeOut directive).
      */
     apr_socket_timeout_get(conn->sock, &current_timeout);
     /* set up the connection filters */
     rc = ap_run_pre_connection(conn->connection, conn->sock);
     if (rc != OK && rc != DONE) {
         conn->connection->aborted = 1;
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                     "proxy: %s: pre_connection setup failed (%d)",
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00963)
+                     "%s: pre_connection setup failed (%d)",
                      proxy_function, rc);
         return rc;
     }
     apr_socket_timeout_set(conn->sock, current_timeout);
 
     return OK;

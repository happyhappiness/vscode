     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "proxy: %s: connection complete to %pI (%s)",
                  proxy_function, backend_addr, conn->hostname);
 
+    /*
+     * save the timout of the socket because core_pre_connection
+     * will set it to base_server->timeout
+     * (core TimeOut directive).
+     */
+    apr_socket_timeout_get(conn->sock, &current_timeout);
     /* set up the connection filters */
     rc = ap_run_pre_connection(conn->connection, conn->sock);
     if (rc != OK && rc != DONE) {
         conn->connection->aborted = 1;
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                      "proxy: %s: pre_connection setup failed (%d)",
                      proxy_function, rc);
         return rc;
     }
+    apr_socket_timeout_set(conn->sock, current_timeout);
 
     return OK;
 }
 
 int ap_proxy_lb_workers(void)
 {

         if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
              ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                           "apr_socket_opt_set(APR_TCP_NODELAY): "
                           "Failed to set");
         }
 
-        /* Set a timeout on the socket */
-        if (worker->timeout_set == 1) {
+        /* Set a timeout for connecting to the backend on the socket */
+        if (worker->conn_timeout_set) {
+            apr_socket_timeout_set(newsock, worker->conn_timeout);
+        }
+        else if (worker->timeout_set == 1) {
             apr_socket_timeout_set(newsock, worker->timeout);
         }
         else if (conf->timeout_set == 1) {
             apr_socket_timeout_set(newsock, conf->timeout);
         }
         else {

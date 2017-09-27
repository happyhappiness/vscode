                             APR_SO_KEEPALIVE, 1)) != APR_SUCCESS) {
                 ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                              "apr_socket_opt_set(SO_KEEPALIVE): Failed to set"
                              " Keepalive");
             }
         }
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
                      "proxy: %s: fam %d socket created to connect to %s",
                      proxy_function, backend_addr->family, worker->hostname);
 
         /* make the connection out of the socket */
         rv = apr_socket_connect(newsock, backend_addr);
 

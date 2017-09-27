              * local machine won't give us an IPv6 socket; hopefully the
              * DNS returned an additional address to try
              */
             backend_addr = backend_addr->next;
             continue;
         }
+        conn->connection = NULL;
 
 #if !defined(TPF) && !defined(BEOS)
         if (worker->recv_buffer_size > 0 &&
             (rv = apr_socket_opt_set(newsock, APR_SO_RCVBUF,
                                      worker->recv_buffer_size))) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,

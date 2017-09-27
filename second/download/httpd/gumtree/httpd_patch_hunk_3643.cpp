                              proxy_function,
                              backend_addr,
                              worker->s->hostname);
                 backend_addr = backend_addr->next;
                 continue;
             }
+
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02824)
+                         "%s: connection established with %pI (%s)",
+                         proxy_function,
+                         backend_addr,
+                         worker->s->hostname);
         }
 
         /* Set a timeout on the socket */
         if (worker->s->timeout_set) {
             apr_socket_timeout_set(newsock, worker->s->timeout);
         }

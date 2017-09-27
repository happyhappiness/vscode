             apr_socket_timeout_set(newsock, conf->timeout);
         }
         else {
              apr_socket_timeout_set(newsock, s->timeout);
         }
 
-        conn->sock   = newsock;
+        conn->sock = newsock;
+
+        if (conn->forward) {
+            forward_info *forward = (forward_info *)conn->forward;
+            /*
+             * For HTTP CONNECT we need to prepend CONNECT request before
+             * sending our actual HTTPS requests.
+             */
+            if (forward->use_http_connect) {
+                rv = send_http_connect(conn, s);
+                /* If an error occurred, loop round and try again */
+                if (rv != APR_SUCCESS) {
+                    conn->sock = NULL;
+                    apr_socket_close(newsock);
+                    loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
+                    ap_log_error(APLOG_MARK, loglevel, rv, s,
+                                 "proxy: %s: attempt to connect to %s:%d "
+                                 "via http CONNECT through %pI (%s) failed",
+                                 proxy_function,
+                                 forward->target_host, forward->target_port,
+                                 backend_addr, worker->hostname);
+                    backend_addr = backend_addr->next;
+                    continue;
+                }
+            }
+        }
+
         connected    = 1;
     }
     /*
      * Put the entire worker to error state if
      * the PROXY_WORKER_IGNORE_ERRORS flag is not set.
      * Altrough some connections may be alive

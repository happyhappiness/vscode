             socket_cleanup(conn);
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00951)
                          "%s: backend socket is disconnected.",
                          proxy_function);
         }
     }
-    while (backend_addr && !connected) {
-        if ((rv = apr_socket_create(&newsock, backend_addr->family,
-                                SOCK_STREAM, APR_PROTO_TCP,
-                                conn->scpool)) != APR_SUCCESS) {
-            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
-            ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(00952)
-                         "%s: error creating fam %d socket for target %s",
-                         proxy_function,
-                         backend_addr->family,
-                         worker->s->hostname);
-            /*
-             * this could be an IPv6 address from the DNS but the
-             * local machine won't give us an IPv6 socket; hopefully the
-             * DNS returned an additional address to try
-             */
-            backend_addr = backend_addr->next;
-            continue;
-        }
-        conn->connection = NULL;
+    while ((backend_addr || conn->uds_path) && !connected) {
+#if APR_HAVE_SYS_UN_H
+        if (conn->uds_path)
+        {
+            struct sockaddr_un sa;
 
-        if (worker->s->recv_buffer_size > 0 &&
-            (rv = apr_socket_opt_set(newsock, APR_SO_RCVBUF,
-                                     worker->s->recv_buffer_size))) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00953)
-                         "apr_socket_opt_set(SO_RCVBUF): Failed to set "
-                         "ProxyReceiveBufferSize, using default");
-        }
+            rv = apr_socket_create(&newsock, AF_UNIX, SOCK_STREAM, 0,
+                                   conn->scpool);
+            if (rv != APR_SUCCESS) {
+                loglevel = APLOG_ERR;
+                ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(02453)
+                             "%s: error creating Unix domain socket for "
+                             "target %s",
+                             proxy_function,
+                             worker->s->hostname);
+                break;
+            }
+            conn->connection = NULL;
 
-        rv = apr_socket_opt_set(newsock, APR_TCP_NODELAY, 1);
-        if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
-             ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00954)
-                          "apr_socket_opt_set(APR_TCP_NODELAY): "
-                          "Failed to set");
-        }
+            sa.sun_family = AF_UNIX;
+            apr_cpystrn(sa.sun_path, conn->uds_path, sizeof(sa.sun_path));
 
-        /* Set a timeout for connecting to the backend on the socket */
-        if (worker->s->conn_timeout_set) {
-            apr_socket_timeout_set(newsock, worker->s->conn_timeout);
-        }
-        else if (worker->s->timeout_set) {
-            apr_socket_timeout_set(newsock, worker->s->timeout);
-        }
-        else if (conf->timeout_set) {
-            apr_socket_timeout_set(newsock, conf->timeout);
-        }
-        else {
-             apr_socket_timeout_set(newsock, s->timeout);
-        }
-        /* Set a keepalive option */
-        if (worker->s->keepalive) {
-            if ((rv = apr_socket_opt_set(newsock,
-                            APR_SO_KEEPALIVE, 1)) != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00955)
-                             "apr_socket_opt_set(SO_KEEPALIVE): Failed to set"
-                             " Keepalive");
-            }
-        }
-        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
-                     "%s: fam %d socket created to connect to %s",
-                     proxy_function, backend_addr->family, worker->s->hostname);
-
-        if (conf->source_address_set) {
-            local_addr = apr_pmemdup(conn->pool, conf->source_address,
-                                     sizeof(apr_sockaddr_t));
-            local_addr->pool = conn->pool;
-            rv = apr_socket_bind(newsock, local_addr);
+            rv = socket_connect_un(newsock, &sa);
             if (rv != APR_SUCCESS) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00956)
-                    "%s: failed to bind socket to local address",
-                    proxy_function);
+                apr_socket_close(newsock);
+                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02454)
+                             "%s: attempt to connect to Unix domain socket "
+                             "%s (%s) failed",
+                             proxy_function,
+                             conn->uds_path,
+                             worker->s->hostname);
+                break;
             }
         }
+        else
+#endif
+        {
+            if ((rv = apr_socket_create(&newsock, backend_addr->family,
+                                        SOCK_STREAM, APR_PROTO_TCP,
+                                        conn->scpool)) != APR_SUCCESS) {
+                loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
+                ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(00952)
+                             "%s: error creating fam %d socket for "
+                             "target %s",
+                             proxy_function,
+                             backend_addr->family,
+                             worker->s->hostname);
+                /*
+                 * this could be an IPv6 address from the DNS but the
+                 * local machine won't give us an IPv6 socket; hopefully the
+                 * DNS returned an additional address to try
+                 */
+                backend_addr = backend_addr->next;
+                continue;
+            }
+            conn->connection = NULL;
 
-        /* make the connection out of the socket */
-        rv = apr_socket_connect(newsock, backend_addr);
+            if (worker->s->recv_buffer_size > 0 &&
+                (rv = apr_socket_opt_set(newsock, APR_SO_RCVBUF,
+                                         worker->s->recv_buffer_size))) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00953)
+                             "apr_socket_opt_set(SO_RCVBUF): Failed to set "
+                             "ProxyReceiveBufferSize, using default");
+            }
 
-        /* if an error occurred, loop round and try again */
-        if (rv != APR_SUCCESS) {
-            apr_socket_close(newsock);
-            loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
-            ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(00957)
-                         "%s: attempt to connect to %pI (%s) failed",
-                         proxy_function,
-                         backend_addr,
-                         worker->s->hostname);
-            backend_addr = backend_addr->next;
-            continue;
+            rv = apr_socket_opt_set(newsock, APR_TCP_NODELAY, 1);
+            if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
+                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00954)
+                             "apr_socket_opt_set(APR_TCP_NODELAY): "
+                             "Failed to set");
+            }
+
+            /* Set a timeout for connecting to the backend on the socket */
+            if (worker->s->conn_timeout_set) {
+                apr_socket_timeout_set(newsock, worker->s->conn_timeout);
+            }
+            else if (worker->s->timeout_set) {
+                apr_socket_timeout_set(newsock, worker->s->timeout);
+            }
+            else if (conf->timeout_set) {
+                apr_socket_timeout_set(newsock, conf->timeout);
+            }
+            else {
+                apr_socket_timeout_set(newsock, s->timeout);
+            }
+            /* Set a keepalive option */
+            if (worker->s->keepalive) {
+                if ((rv = apr_socket_opt_set(newsock,
+                                             APR_SO_KEEPALIVE, 1)) != APR_SUCCESS) {
+                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00955)
+                                 "apr_socket_opt_set(SO_KEEPALIVE): Failed to set"
+                                 " Keepalive");
+                }
+            }
+            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, s,
+                         "%s: fam %d socket created to connect to %s",
+                         proxy_function, backend_addr->family, worker->s->hostname);
+
+            if (conf->source_address_set) {
+                local_addr = apr_pmemdup(conn->pool, conf->source_address,
+                                         sizeof(apr_sockaddr_t));
+                local_addr->pool = conn->pool;
+                rv = apr_socket_bind(newsock, local_addr);
+                if (rv != APR_SUCCESS) {
+                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00956)
+                                 "%s: failed to bind socket to local address",
+                                 proxy_function);
+                }
+            }
+
+            /* make the connection out of the socket */
+            rv = apr_socket_connect(newsock, backend_addr);
+
+            /* if an error occurred, loop round and try again */
+            if (rv != APR_SUCCESS) {
+                apr_socket_close(newsock);
+                loglevel = backend_addr->next ? APLOG_DEBUG : APLOG_ERR;
+                ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(00957)
+                             "%s: attempt to connect to %pI (%s) failed",
+                             proxy_function,
+                             backend_addr,
+                             worker->s->hostname);
+                backend_addr = backend_addr->next;
+                continue;
+            }
         }
 
         /* Set a timeout on the socket */
         if (worker->s->timeout_set) {
             apr_socket_timeout_set(newsock, worker->s->timeout);
         }

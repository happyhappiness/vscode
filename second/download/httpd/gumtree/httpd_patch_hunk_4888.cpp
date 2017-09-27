         }
         else if (rc == 229) {
             /* Parse the port out of the EPSV reply. */
             data_port = parse_epsv_reply(ftpmessage);
 
             if (data_port) {
-                apr_sockaddr_t *epsv_addr;
+                apr_sockaddr_t *remote_addr, epsv_addr;
 
                 ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                               "EPSV contacting remote host on port %d", data_port);
 
-                if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01040)
-                                  "error creating EPSV socket");
+                /* Retrieve the client's address. */
+                rv = apr_socket_addr_get(&remote_addr, APR_REMOTE, sock);
+                if (rv == APR_SUCCESS) {
+                    /* Take a shallow copy of the server address to
+                     * modify; the _addr_get function gives back a
+                     * pointer to the socket's internal structure.
+                     * This is awkward given current APR network
+                     * interfaces. */
+                    epsv_addr = *remote_addr;
+                    epsv_addr.port = data_port;
+#if APR_HAVE_IPV6
+                    if (epsv_addr.family == APR_INET6) {
+                        epsv_addr.sa.sin6.sin6_port = htons(data_port);
+                    }
+                    else
+#endif
+                    {
+                        epsv_addr.sa.sin.sin_port = htons(data_port);
+                    }
+                    rv = apr_socket_create(&data_sock, epsv_addr.family, SOCK_STREAM, 0, r->pool);
+                }
+
+                if (rv != APR_SUCCESS) {
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01040) 
+                                  "could not establish socket for client data connection");
                     proxy_ftp_cleanup(r, backend);
                     return HTTP_INTERNAL_SERVER_ERROR;
                 }
 
                 if (conf->recv_buffer_size > 0
                         && (rv = apr_socket_opt_set(data_sock, APR_SO_RCVBUF,

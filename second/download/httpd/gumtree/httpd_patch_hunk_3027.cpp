             /* Parse the port out of the EPSV reply. */
             data_port = parse_epsv_reply(ftpmessage);
 
             if (data_port) {
                 apr_sockaddr_t *epsv_addr;
 
-                ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
-                             "proxy: FTP: EPSV contacting remote host on port %d",
-                             data_port);
+                ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
+                              "EPSV contacting remote host on port %d", data_port);
 
                 if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                                  "proxy: FTP: error creating EPSV socket");
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01040)
+                                  "error creating EPSV socket");
                     proxy_ftp_cleanup(r, backend);
                     return HTTP_INTERNAL_SERVER_ERROR;
                 }
 
                 if (conf->recv_buffer_size > 0
                         && (rv = apr_socket_opt_set(data_sock, APR_SO_RCVBUF,
                                                     conf->recv_buffer_size))) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                                  "proxy: FTP: apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01041)
+                                  "apr_socket_opt_set(SO_RCVBUF): Failed to "
+                                  "set ProxyReceiveBufferSize, using default");
                 }
 
                 rv = apr_socket_opt_set(data_sock, APR_TCP_NODELAY, 1);
                 if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                                 "apr_socket_opt_set(APR_TCP_NODELAY): Failed to set");
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01042)
+                                  "apr_socket_opt_set(APR_TCP_NODELAY): "
+                                  "Failed to set");
                 }
 
                 /* make the connection */
                 apr_socket_addr_get(&data_addr, APR_REMOTE, sock);
                 apr_sockaddr_ip_get(&data_ip, data_addr);
                 apr_sockaddr_info_get(&epsv_addr, data_ip, connect_addr->family, data_port, 0, p);
                 rv = apr_socket_connect(data_sock, epsv_addr);
                 if (rv != APR_SUCCESS) {
-                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
-                                 "proxy: FTP: EPSV attempt to connect to %pI failed - Firewall/NAT?", epsv_addr);
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01043)
+                                  "EPSV attempt to connect to %pI failed - "
+                                  "Firewall/NAT?", epsv_addr);
                     return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, apr_psprintf(r->pool,
                                                                            "EPSV attempt to connect to %pI failed - firewall/NAT?", epsv_addr));
                 }
                 else {
                     connect = 1;
                 }

             /* Parse the port out of the EPSV reply. */
             data_port = parse_epsv_reply(ftpmessage);
 
             if (data_port) {
                 apr_sockaddr_t *epsv_addr;
 
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                       "proxy: FTP: EPSV contacting remote host on port %d",
+                ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
+                             "proxy: FTP: EPSV contacting remote host on port %d",
                              data_port);
 
                 if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                   "proxy: FTP: error creating EPSV socket");
                     proxy_ftp_cleanup(r, backend);
                     return HTTP_INTERNAL_SERVER_ERROR;
                 }
 
-#if !defined (TPF) && !defined(BEOS)
                 if (conf->recv_buffer_size > 0
                         && (rv = apr_socket_opt_set(data_sock, APR_SO_RCVBUF,
                                                     conf->recv_buffer_size))) {
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                   "proxy: FTP: apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                 }
-#endif
 
                 rv = apr_socket_opt_set(data_sock, APR_TCP_NODELAY, 1);
                 if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "apr_socket_opt_set(APR_TCP_NODELAY): Failed to set");
                 }

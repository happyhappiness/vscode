                apr_sockaddr_t *pasv_addr;
                apr_port_t pasvport = (p1 << 8) + p0;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                          "proxy: FTP: PASV contacting host %d.%d.%d.%d:%d",
                             h3, h2, h1, h0, pasvport);

                if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: error creating PASV socket");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

#if !defined (TPF) && !defined(BEOS)
                if (conf->recv_buffer_size > 0 
                        && (rv = apr_socket_opt_set(data_sock, APR_SO_RCVBUF,
                                                    conf->recv_buffer_size))) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                }
#endif

                /* make the connection */
                apr_sockaddr_info_get(&pasv_addr, apr_psprintf(p, "%d.%d.%d.%d", h3, h2, h1, h0), connect_addr->family, pasvport, 0, p);
                rv = apr_connect(data_sock, pasv_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                                 "proxy: FTP: PASV attempt to connect to %pI failed - Firewall/NAT?", pasv_addr);
                    return ap_proxyerror(r, HTTP_BAD_GATEWAY, apr_psprintf(r->pool,
                                                                           "PASV attempt to connect to %pI failed - firewall/NAT?", pasv_addr));

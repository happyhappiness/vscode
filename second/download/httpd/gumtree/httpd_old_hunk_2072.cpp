                                                    conf->recv_buffer_size))) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                }
#endif

                /* make the connection */
                apr_sockaddr_info_get(&pasv_addr, apr_psprintf(p, "%d.%d.%d.%d", h3, h2, h1, h0), connect_addr->family, pasvport, 0, p);
                rv = apr_socket_connect(data_sock, pasv_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                                 "proxy: FTP: PASV attempt to connect to %pI failed - Firewall/NAT?", pasv_addr);

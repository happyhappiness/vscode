                                                    conf->recv_buffer_size))) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                }
#endif

                rv = apr_socket_opt_set(data_sock, APR_TCP_NODELAY, 1);
                if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                 "apr_socket_opt_set(APR_TCP_NODELAY): Failed to set");
                }

                /* make the connection */
                apr_socket_addr_get(&data_addr, APR_REMOTE, sock);
                apr_sockaddr_ip_get(&data_ip, data_addr);
                apr_sockaddr_info_get(&epsv_addr, data_ip, connect_addr->family, data_port, 0, p);
                rv = apr_socket_connect(data_sock, epsv_addr);
                if (rv != APR_SUCCESS) {

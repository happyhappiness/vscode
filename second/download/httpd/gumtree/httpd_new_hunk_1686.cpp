                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: error creating PASV socket");
                    proxy_ftp_cleanup(r, backend);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

                if (conf->recv_buffer_size > 0
                        && (rv = apr_socket_opt_set(data_sock, APR_SO_RCVBUF,
                                                    conf->recv_buffer_size))) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                }

                rv = apr_socket_opt_set(data_sock, APR_TCP_NODELAY, 1);
                if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                 "apr_socket_opt_set(APR_TCP_NODELAY): Failed to set");
                }

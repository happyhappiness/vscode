
            if (pstr != NULL && (sscanf(pstr,
                 "%d,%d,%d,%d,%d,%d", &h3, &h2, &h1, &h0, &p1, &p0) == 6)) {

                apr_sockaddr_t *pasv_addr;
                apr_port_t pasvport = (p1 << 8) + p0;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01044)
                              "PASV contacting host %d.%d.%d.%d:%d",
                              h3, h2, h1, h0, pasvport);

                if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01045)
                                  "error creating PASV socket");
                    proxy_ftp_cleanup(r, backend);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

                if (conf->recv_buffer_size > 0
                        && (rv = apr_socket_opt_set(data_sock, APR_SO_RCVBUF,
                                                    conf->recv_buffer_size))) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01046)
                                  "apr_socket_opt_set(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                }

                rv = apr_socket_opt_set(data_sock, APR_TCP_NODELAY, 1);
                if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01047)
                                  "apr_socket_opt_set(APR_TCP_NODELAY): "
                                  "Failed to set");
                }

                /* make the connection */
                apr_sockaddr_info_get(&pasv_addr, apr_psprintf(p, "%d.%d.%d.%d", h3, h2, h1, h0), connect_addr->family, pasvport, 0, p);
                rv = apr_socket_connect(data_sock, pasv_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01048)
                                  "PASV attempt to connect to %pI failed - Firewall/NAT?", pasv_addr);
                    return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, apr_psprintf(r->pool,
                                                                           "PASV attempt to connect to %pI failed - firewall/NAT?", pasv_addr));
                }
                else {
                    connect = 1;
                }

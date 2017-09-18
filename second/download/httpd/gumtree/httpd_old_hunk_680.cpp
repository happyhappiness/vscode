                data_port = atoi(pstr + 3);

                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                       "proxy: FTP: EPSV contacting remote host on port %d",
                             data_port);

                if ((rv = apr_socket_create(&data_sock, APR_INET, SOCK_STREAM, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: error creating EPSV socket");
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

#if !defined (TPF) && !defined(BEOS)
                if (conf->recv_buffer_size > 0 && (rv = apr_setsocketopt(data_sock, APR_SO_RCVBUF,
                                                 conf->recv_buffer_size))) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: setsockopt(SO_RCVBUF): Failed to set ProxyReceiveBufferSize, using default");
                }
#endif

                /* make the connection */
                apr_socket_addr_get(&data_addr, APR_REMOTE, sock);
                apr_sockaddr_ip_get(&data_ip, data_addr);
                apr_sockaddr_info_get(&epsv_addr, data_ip, APR_INET, data_port, 0, p);
                rv = apr_connect(data_sock, epsv_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                                 "proxy: FTP: EPSV attempt to connect to %pI failed - Firewall/NAT?", epsv_addr);
                    return ap_proxyerror(r, HTTP_BAD_GATEWAY, apr_psprintf(r->pool,
                                                                           "EPSV attempt to connect to %pI failed - firewall/NAT?", epsv_addr));

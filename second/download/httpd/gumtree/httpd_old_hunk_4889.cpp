                if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01042)
                                  "apr_socket_opt_set(APR_TCP_NODELAY): "
                                  "Failed to set");
                }

                /* make the connection */
                apr_socket_addr_get(&data_addr, APR_REMOTE, sock);
                apr_sockaddr_ip_get(&data_ip, data_addr);
                apr_sockaddr_info_get(&epsv_addr, data_ip, connect_addr->family, data_port, 0, p);
                rv = apr_socket_connect(data_sock, epsv_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01043)
                                  "EPSV attempt to connect to %pI failed - "
                                  "Firewall/NAT?", epsv_addr);
                    return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, apr_psprintf(r->pool,
                                                                           "EPSV attempt to connect to %pI failed - firewall/NAT?", epsv_addr));
                }
                else {
                    connect = 1;
                }
            }
        }
    }


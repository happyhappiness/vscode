                if (rv != APR_SUCCESS && rv != APR_ENOTIMPL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01042)
                                  "apr_socket_opt_set(APR_TCP_NODELAY): "
                                  "Failed to set");
                }

                rv = apr_socket_connect(data_sock, &epsv_addr);
                if (rv != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01043)
                                  "EPSV attempt to connect to %pI failed - "
                                  "Firewall/NAT?", &epsv_addr);
                    return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, apr_psprintf(r->pool,
                                                                           "EPSV attempt to connect to %pI failed - firewall/NAT?", &epsv_addr));
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                                  "connected data socket to %pI", &epsv_addr);
                    connect = 1;
                }
            }
        }
    }


                proxy_ssl_check_peer_ok = FALSE;
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02004)
                              "SSL Proxy: Peer certificate is expired");
            }
        }
        if ((sc->proxy_ssl_check_peer_name != SSL_ENABLED_FALSE) &&
            ((sc->proxy_ssl_check_peer_cn != SSL_ENABLED_FALSE) ||
             (sc->proxy_ssl_check_peer_name == SSL_ENABLED_TRUE)) &&
            hostname_note) {
            apr_table_unset(c->notes, "proxy-request-hostname");
            if (!cert
                || modssl_X509_match_name(c->pool, cert, hostname_note,
                                          TRUE, server) == FALSE) {
                proxy_ssl_check_peer_ok = FALSE;
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02411)
                              "SSL Proxy: Peer certificate does not match "
                              "for hostname %s", hostname_note);
            }
        }
        else if ((sc->proxy_ssl_check_peer_cn == SSL_ENABLED_TRUE) &&
            hostname_note) {
            const char *hostname;
            int match = 0;

            hostname = ssl_var_lookup(NULL, server, c, NULL,
                                      "SSL_CLIENT_S_DN_CN");

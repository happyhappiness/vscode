            if (!r->hostname) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02031)
                            "Hostname %s provided via SNI, but no hostname"
                            " provided in HTTP request", servername);
                return HTTP_BAD_REQUEST;
            }
            if (r->server != handshakeserver 
                && !ssl_server_compatible(sslconn->server, r->server)) {
                /* 
                 * The request does not select the virtual host that was
                 * selected by the SNI and its SSL parameters are different
                 */
                
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02032)
                             "Hostname %s provided via SNI and hostname %s provided"
                             " via HTTP have no compatible SSL setup",
                             servername, r->hostname);
                return HTTP_MISDIRECTED_REQUEST;
            }
        }
        else if (((sc->strict_sni_vhost_check == SSL_ENABLED_TRUE)
                  || hssc->strict_sni_vhost_check == SSL_ENABLED_TRUE)

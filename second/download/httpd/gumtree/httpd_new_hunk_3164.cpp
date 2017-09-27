
        /*
         * The SNI extension supplied a hostname. So don't accept requests
         * with either no hostname or a different hostname.
         */
        if (!r->hostname) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02031)
                        "Hostname %s provided via SNI, but no hostname"
                        " provided in HTTP request", servername);
            return HTTP_BAD_REQUEST;
        }
        rv = apr_parse_addr_port(&host, &scope_id, &port, r->hostname, r->pool);
        if (rv != APR_SUCCESS || scope_id) {
            return HTTP_BAD_REQUEST;
        }
        if (strcasecmp(host, servername)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server, APLOGNO(02032)
                        "Hostname %s provided via SNI and hostname %s provided"
                        " via HTTP are different", servername, host);
            return HTTP_BAD_REQUEST;
        }
    }
    else if (((sc->strict_sni_vhost_check == SSL_ENABLED_TRUE)

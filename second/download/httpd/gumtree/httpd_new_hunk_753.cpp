    }

    /*
     * Support for SSLRequireSSL directive
     */
    if (dc->bSSLRequired && !ssl) {
        if (sc->enabled == SSL_ENABLED_OPTIONAL) {
            /* This vhost was configured for optional SSL, just tell the
             * client that we need to upgrade.
             */
            apr_table_setn(r->err_headers_out, "Upgrade", "TLS/1.0, HTTP/1.1");
            apr_table_setn(r->err_headers_out, "Connection", "Upgrade");

            return HTTP_UPGRADE_REQUIRED;
        }

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "access to %s failed, reason: %s",
                      r->filename, "SSL connection required");

        /* remember forbidden access for strict require option */
        apr_table_setn(r->notes, "ssl-access-forbidden", "1");

        return HTTP_FORBIDDEN;
    }

    /*
     * Check to see if SSL protocol is on
     */
    if (!((sc->enabled == SSL_ENABLED_TRUE) || (sc->enabled == SSL_ENABLED_OPTIONAL) || ssl)) {
        return DECLINED;
    }
    /*
     * Support for per-directory reconfigured SSL connection parameters.
     *
     * This is implemented by forcing an SSL renegotiation with the
     * reconfigured parameter suite. But Apache's internal API processing
     * makes our life very hard here, because when internal sub-requests occur

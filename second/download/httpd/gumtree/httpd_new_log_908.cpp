(dc->bSSLRequired && !ssl) {
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
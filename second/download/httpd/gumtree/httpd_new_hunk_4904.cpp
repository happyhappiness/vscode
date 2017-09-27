            }
            X509_free(cert);
        }
        if ((sc->proxy_ssl_check_peer_cn != SSL_ENABLED_FALSE) &&
            hostname_note) {
            const char *hostname;
            int match = 0;

            hostname = ssl_var_lookup(NULL, server, c, NULL,
                                      "SSL_CLIENT_S_DN_CN");
            apr_table_unset(c->notes, "proxy-request-hostname");

            /* Do string match or simplest wildcard match if that
             * fails. */
            match = strcasecmp(hostname, hostname_note) == 0;
            if (!match && strncmp(hostname, "*.", 2) == 0) {
                const char *p = ap_strchr_c(hostname_note, '.');
                
                match = p && strcasecmp(p, hostname + 1) == 0;
            }

            if (!match) {
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02005)
                              "SSL Proxy: Peer certificate CN mismatch:"
                              " Certificate CN: %s Requested hostname: %s",
                              hostname, hostname_note);
                /* ensure that the SSL structures etc are freed, etc: */
                ssl_filter_io_shutdown(filter_ctx, c, 1);

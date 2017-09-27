                              "SSL Proxy: Peer certificate is expired");
                if (cert) {
                    X509_free(cert);
                }
                /* ensure that the SSL structures etc are freed, etc: */
                ssl_filter_io_shutdown(filter_ctx, c, 1);
                apr_table_set(c->notes, "SSL_connect_rv", "err");
                return HTTP_BAD_GATEWAY;
            }
            X509_free(cert);
        }
        if ((sc->proxy_ssl_check_peer_cn == SSL_ENABLED_TRUE)
            && hostname_note) {
            const char *hostname;

            hostname = ssl_var_lookup(NULL, server, c, NULL,
                                      "SSL_CLIENT_S_DN_CN");
            apr_table_unset(c->notes, "proxy-request-hostname");
            if (strcasecmp(hostname, hostname_note)) {
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                              "SSL Proxy: Peer certificate CN mismatch:"
                              " Certificate CN: %s Requested hostname: %s",
                              hostname, hostname_note);
                /* ensure that the SSL structures etc are freed, etc: */
                ssl_filter_io_shutdown(filter_ctx, c, 1);
                apr_table_set(c->notes, "SSL_connect_rv", "err");
                return HTTP_BAD_GATEWAY;
            }
        }

        apr_table_set(c->notes, "SSL_connect_rv", "ok");
        return APR_SUCCESS;
    }

    if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
        bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)
                                     (filter_ctx->pbioRead->ptr);

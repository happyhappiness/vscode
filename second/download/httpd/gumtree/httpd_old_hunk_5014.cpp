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
                apr_table_setn(c->notes, "SSL_connect_rv", "err");
                return HTTP_BAD_GATEWAY;
            }
        }

        apr_table_setn(c->notes, "SSL_connect_rv", "ok");
        return APR_SUCCESS;
    }

    if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
        bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)

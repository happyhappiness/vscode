                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                              "SSL Proxy: Peer certificate CN mismatch:"
                              " Certificate CN: %s Requested hostname: %s",
                              hostname, hostname_note);
                /* ensure that the SSL structures etc are freed, etc: */
                ssl_filter_io_shutdown(filter_ctx, c, 1);
                return HTTP_BAD_GATEWAY;
            }
        }

        return APR_SUCCESS;
    }

    if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
        bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)
                                     (filter_ctx->pbioRead->ptr);

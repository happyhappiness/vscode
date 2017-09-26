    if (SSL_is_init_finished(filter_ctx->pssl)) {
        return APR_SUCCESS;
    }

    if (sslconn->is_proxy) {
        if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                          "SSL Proxy connect failed");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
            /* ensure that the SSL structures etc are freed, etc: */
            ssl_filter_io_shutdown(filter_ctx, c, 1);
            return HTTP_BAD_GATEWAY;
        }

        return APR_SUCCESS;
    }

    if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
        bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)
                                     (filter_ctx->pbioRead->ptr);
        bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)
                                       (filter_ctx->pbioWrite->ptr);
        apr_status_t rc = inctx->rc ? inctx->rc : outctx->rc ;
        ssl_err = SSL_get_error(filter_ctx->pssl, n);

        if (ssl_err == SSL_ERROR_ZERO_RETURN) {
            /*
             * The case where the connection was closed before any data
             * was transferred. That's not a real error and can occur
             * sporadically with some clients.
             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
                         "SSL handshake stopped: connection was closed");
        }
        else if (ssl_err == SSL_ERROR_WANT_READ) {
            /*
             * This is in addition to what was present earlier. It is
             * borrowed from openssl_state_machine.c [mod_tls].
             * TBD.
             */
            outctx->rc = APR_EAGAIN;
            return SSL_ERROR_WANT_READ;
        }

            /*
             * Log SSL errors and any unexpected conditions.
             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
                          "SSL library error %d in handshake "
                          "(server %s)", ssl_err,
                          ssl_util_vhostid(c->pool, c->base_server));
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);

        }
        if (inctx->rc == APR_SUCCESS) {
            inctx->rc = APR_EGENERAL;
        }

        return ssl_filter_io_shutdown(filter_ctx, c, 1);
    }

    /*
     * Check for failed client authentication
     */
    verify_result = SSL_get_verify_result(filter_ctx->pssl);


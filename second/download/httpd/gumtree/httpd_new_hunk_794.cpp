             * ssl_io_filter_error will disable the ssl filters when it
             * sees this status code.
             */
            return HTTP_BAD_REQUEST;
        }
        else if (ssl_err == SSL_ERROR_SYSCALL) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
                          "SSL handshake interrupted by system "
                          "[Hint: Stop button pressed in browser?!]");
        }
        else /* if (ssl_err == SSL_ERROR_SSL) */ {
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

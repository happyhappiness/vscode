             * ssl_io_filter_error will disable the ssl filters when it
             * sees this status code.
             */
            return MODSSL_ERROR_HTTP_ON_HTTPS;
        }
        else if (ssl_err == SSL_ERROR_SYSCALL) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rc, c,
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
                          ssl_util_vhostid(c->pool, server));
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);

        }

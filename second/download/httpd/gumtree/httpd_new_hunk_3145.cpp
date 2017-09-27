            /*
             * If OpenSSL wants to write more, and we were nonblocking,
             * report as an EAGAIN.  Otherwise loop, pushing more
             * data at the network filter.
             *
             * (This is usually the case when the client forces an SSL
             * renegotiation which is handled implicitly by OpenSSL.)
             */
            outctx->rc = APR_EAGAIN;
        }
        else if (ssl_err == SSL_ERROR_SYSCALL) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c, APLOGNO(01993)
                          "SSL output filter write failed.");
        }
        else /* if (ssl_err == SSL_ERROR_SSL) */ {
            /*
             * Log SSL errors
             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c, APLOGNO(01994)
                          "SSL library error %d writing data", ssl_err);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, mySrvFromConn(c));
        }
        if (outctx->rc == APR_SUCCESS) {
            outctx->rc = APR_EGENERAL;
        }

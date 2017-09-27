                    if (inctx->block == APR_NONBLOCK_READ) {
                        break;
                    }
                    continue;  /* Blocking and nothing yet?  Try again. */
                }
                else {
                    ap_log_cerror(APLOG_MARK, APLOG_INFO, inctx->rc, c,
                                  "SSL input filter read failed.");
                }
            }
            else /* if (ssl_err == SSL_ERROR_SSL) */ {
                /*
                 * Log SSL errors and any unexpected conditions.
                 */
                ap_log_cerror(APLOG_MARK, APLOG_INFO, inctx->rc, c,
                              "SSL library error %d reading data", ssl_err);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, mySrvFromConn(c));

            }
            if (inctx->rc == APR_SUCCESS) {
                inctx->rc = APR_EGENERAL;

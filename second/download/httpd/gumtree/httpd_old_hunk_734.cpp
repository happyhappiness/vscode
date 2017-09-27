                    if (inctx->block == APR_NONBLOCK_READ) {
                        break;
                    }
                    continue;  /* Blocking and nothing yet?  Try again. */
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_INFO, inctx->rc, c->base_server,
                                "SSL input filter read failed.");
                }
            }
            else /* if (ssl_err == SSL_ERROR_SSL) */ {
                /*
                 * Log SSL errors and any unexpected conditions.
                 */
                ap_log_error(APLOG_MARK, APLOG_INFO, inctx->rc, c->base_server,
                            "SSL library error %d reading data", ssl_err);
                ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);

            }
            if (inctx->rc == APR_SUCCESS) {
                inctx->rc = APR_EGENERAL;
            }

                    }
                    if (inctx->block == APR_NONBLOCK_READ) {
                        break;
                    }
                    continue;  /* Blocking and nothing yet?  Try again. */
                }
                else {
                    ap_log_cerror(APLOG_MARK, APLOG_INFO, inctx->rc, c, APLOGNO(01991)
                                  "SSL input filter read failed.");
                }
            }
            else /* if (ssl_err == SSL_ERROR_SSL) */ {

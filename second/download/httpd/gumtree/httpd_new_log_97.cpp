ap_log_error(APLOG_MARK, APLOG_INFO, inctx->rc, c->base_server,
                            "SSL library error %d reading data", ssl_err);
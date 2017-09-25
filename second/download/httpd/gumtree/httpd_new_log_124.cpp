ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
                         "SSL library error %d writing data", ssl_err);
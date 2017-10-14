ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         f->c->base_server,
                         "SSL handshake failed: HTTP spoken on HTTPS port; "
                         "trying to send HTML error page");
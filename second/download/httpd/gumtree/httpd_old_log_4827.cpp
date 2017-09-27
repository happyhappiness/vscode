ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                         "SSL handshake failed: HTTP spoken on HTTPS port; "
                         "trying to send HTML error page");
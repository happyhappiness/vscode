ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, r->server,
                     "proxy: FTP: Content-Encoding set to %s",
                     r->content_encoding);
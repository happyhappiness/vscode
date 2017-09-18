ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                     "proxy: FTP: Content-Type set to %s", r->content_type);
ap_log_error(APLOG_MARK, APLOG_INFO | APLOG_NOERRNO, 0, r->server,
            "cached version of %s being served", r->uri);
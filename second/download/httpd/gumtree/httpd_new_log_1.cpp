ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, r->server,
            "handler \"%s\" not found for: %s", r->handler, r->filename);
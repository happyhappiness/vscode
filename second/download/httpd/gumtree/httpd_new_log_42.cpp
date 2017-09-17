ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, r,
            "handler \"%s\" not found for: %s", r->handler, r->filename);
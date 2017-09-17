ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "internal error: bad expires code: %s", r->filename);
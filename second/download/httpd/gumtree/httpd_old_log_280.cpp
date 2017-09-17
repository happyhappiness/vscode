ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                        "Invalid tag for set directive in %s", r->filename);
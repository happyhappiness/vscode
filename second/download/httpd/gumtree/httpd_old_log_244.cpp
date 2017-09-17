ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                        "unknown parameter \"%s\" to tag include in %s",
                        tag, r->filename);
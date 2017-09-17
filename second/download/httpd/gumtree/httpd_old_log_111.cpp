ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_CRIT, r->server,
                    "configuration error:  couldn't %s: %s", phase, r->uri);
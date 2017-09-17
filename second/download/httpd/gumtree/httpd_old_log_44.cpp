ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, r->server, "%s: %s",
                        filename, errmsg);
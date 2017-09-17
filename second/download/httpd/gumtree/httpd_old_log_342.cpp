ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_INFO, r->server,
                        ref ? "Fixed spelling: %s to %s from %s"
                        : "Fixed spelling: %s to %s",
                        r->uri, nuri, ref);
ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                        "chunked Transfer-Encoding forbidden: %s", r->uri);
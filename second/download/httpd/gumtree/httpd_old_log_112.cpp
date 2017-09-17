ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "client sent illegal HTTP/0.9 request: %s", r->uri);
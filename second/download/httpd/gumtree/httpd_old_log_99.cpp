ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "%s with body is not allowed for %s", r->method, r->uri);
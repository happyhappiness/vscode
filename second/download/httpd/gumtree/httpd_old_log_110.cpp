ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                        "Invalid error redirection directive: %s",
                        custom_response);
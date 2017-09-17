ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                            "invalid CGI ref \"%s\" in %s", tag_val, file);
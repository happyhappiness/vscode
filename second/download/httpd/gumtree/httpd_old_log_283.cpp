ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                                "httpd: exec used but not allowed in %s",
                                r->filename);
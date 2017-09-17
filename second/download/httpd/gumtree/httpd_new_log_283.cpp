ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                                "httpd: exec used but not allowed in %s",
                                r->filename);
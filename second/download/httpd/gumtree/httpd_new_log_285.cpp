ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "httpd: premature EOF in parsed file %s",
                            r->filename);
ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                            "httpd: premature EOF in parsed file %s",
                            r->filename);
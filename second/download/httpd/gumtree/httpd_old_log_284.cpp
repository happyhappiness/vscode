ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                            "httpd: unknown directive \"%s\" "
                            "in parsed doc %s",
                            directive, r->filename);
ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "httpd: unknown directive \"%s\" "
                            "in parsed doc %s",
                            directive, r->filename);
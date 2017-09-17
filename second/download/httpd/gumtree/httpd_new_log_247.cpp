ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                            "invalid CGI ref \"%s\" in %s", tag_val, file);
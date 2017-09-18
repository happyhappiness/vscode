ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                    "invalid CGI ref \"%s\" in %s", tag_val, file);
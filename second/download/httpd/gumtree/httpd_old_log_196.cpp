ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" to tag if in %s", tag, 
                            r->filename);
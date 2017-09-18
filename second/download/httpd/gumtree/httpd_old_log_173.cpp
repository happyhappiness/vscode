ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" in tag echo of %s",
                            tag, r->filename);
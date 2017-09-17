ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "unknown parameter \"%s\" to tag exec in %s",
                        tag, file);
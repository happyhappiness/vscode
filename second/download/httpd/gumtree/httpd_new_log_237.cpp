ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "invalid directory name in map file: %s", r->uri);
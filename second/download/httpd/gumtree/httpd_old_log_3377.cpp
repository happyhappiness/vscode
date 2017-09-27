ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                        "Could not open group file: %s",
                        conf->groupfile);
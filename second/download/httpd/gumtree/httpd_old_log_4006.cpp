ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                    "cannot read directory for multi: %s", neg->dir_name);
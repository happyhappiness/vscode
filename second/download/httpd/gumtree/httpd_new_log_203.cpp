ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "printenv directive does not take tags in %s", 
                        r->filename);
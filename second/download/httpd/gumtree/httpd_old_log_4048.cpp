ap_log_rerror(APLOG_MARK, APLOG_ERR, result, r,
                    MODNAME ": read failed: %s", r->filename);
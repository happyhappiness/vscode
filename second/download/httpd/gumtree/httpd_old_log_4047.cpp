ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    MODNAME ": can't read `%s'", r->filename);
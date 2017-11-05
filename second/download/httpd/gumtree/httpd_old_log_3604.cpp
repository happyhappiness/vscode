ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                    MODNAME ": couldn't spawn uncompress process: %s", r->uri);
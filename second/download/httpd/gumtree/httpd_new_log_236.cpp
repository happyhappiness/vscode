ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "invalid base directive in map file: %s", r->uri);
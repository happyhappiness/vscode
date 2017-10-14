ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "Invalid expression in file %s: Token '-A' must be followed by a URI string.",
                    r->filename);
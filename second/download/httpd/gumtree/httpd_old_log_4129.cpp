ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                "malformed header in meta file: %s", r->filename);
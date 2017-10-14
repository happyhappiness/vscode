ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                          "file permissions deny server access: %s", r->filename);
ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Directory index forbidden by "
                      "Options directive: %s", r->filename);
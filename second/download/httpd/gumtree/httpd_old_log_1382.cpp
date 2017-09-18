ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                      "couldn't set child process attributes: %s", r->filename);
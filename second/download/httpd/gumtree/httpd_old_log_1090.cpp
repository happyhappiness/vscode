ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                          "couldn't create child process: %d: %s", rc,
                          r->filename);
ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "don't know how to spawn cmd child process: %s",
                      r->filename);
ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "object is not a file, directory or symlink: %s",
                  r->filename);
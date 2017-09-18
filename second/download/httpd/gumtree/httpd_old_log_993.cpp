ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                  "symlink doesn't point to a file or "
                                  "directory: %s",
                                  r->filename);
ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|loglevel,
                                  0, r, error_fmt, tag_val, r->filename);
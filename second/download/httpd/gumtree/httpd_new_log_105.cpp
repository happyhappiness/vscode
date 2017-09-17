ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                "object is not a file, directory or symlink: %s",
                r->filename);
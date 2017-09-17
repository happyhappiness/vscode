ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                "object is not a file, directory or symlink: %s",
                r->filename);
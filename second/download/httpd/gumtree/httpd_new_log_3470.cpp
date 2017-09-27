ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                            "asynchronous I/O not supported: %s",
                            r->filename);
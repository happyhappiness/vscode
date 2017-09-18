ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI asynchronous I/O not supported: %s", 
                          r->filename);
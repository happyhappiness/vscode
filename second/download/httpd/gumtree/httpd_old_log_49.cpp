ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                                   "ISAPI %s asynch I/O request refused", 
                                   r->filename);
ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "Syntax error in type map --- no ':': %s", r->filename);
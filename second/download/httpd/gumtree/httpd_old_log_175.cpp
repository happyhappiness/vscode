ap_log_rerror(APLOG_MARK, APLOG_ERR | (rv ? 0 : APLOG_NOERRNO),
                          rv, r, error_fmt, to_send, r->filename);
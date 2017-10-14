ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[strict] Invalid host name '%s'%s%.6s",
                  host, *ch ? ", problem near: " : "", ch);
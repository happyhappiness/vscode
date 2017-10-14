ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02415)
                  "[strict] Invalid host name '%s'%s%.6s",
                  host, *ch ? ", problem near: " : "", ch);
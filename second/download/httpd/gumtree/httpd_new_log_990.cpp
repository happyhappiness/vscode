ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      "configuration error:  couldn't %s: %s", phase, r->uri);
ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                      "lb_heartbeat: No server for worker %s", (*worker)->name);
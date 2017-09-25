ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "r->uri = %s", r->uri ? r->uri : "(unexpectedly NULL)");
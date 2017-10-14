ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "client used wrong authentication scheme: %s", r->uri);
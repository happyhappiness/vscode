ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, SESSION_PREFIX
                      "excluded by configuration for: %s", r->uri);
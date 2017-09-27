ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                      "auth phase '%s' gave status %d: %s", phase,
                      status, r->uri);
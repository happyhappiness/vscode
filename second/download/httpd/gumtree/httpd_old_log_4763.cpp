ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                  "Faking HTTP Basic Auth header: \"Authorization: %s\"",
                  auth_line);
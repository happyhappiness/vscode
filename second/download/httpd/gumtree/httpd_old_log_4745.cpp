ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                      "failed to acquire database connection to remove "
                      "session with key '%s'", key);
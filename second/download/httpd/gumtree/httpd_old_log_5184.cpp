ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "ServerLimit of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         server_limit, MAX_SERVER_LIMIT);
ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00181)
                         "MaxRequestWorkers of %d exceeds ServerLimit value "
                         "of %d, decreasing to match",
                         ap_daemons_limit, server_limit);
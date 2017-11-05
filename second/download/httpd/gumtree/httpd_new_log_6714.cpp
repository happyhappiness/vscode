ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                     APLOGNO(02531) "winnt_accept: Listen protocol '%s' has "
                     "no known accept filter. Using 'none' instead",
                     lr->protocol);
ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         ap_server_conf,
                         "server reached MaxThreadsPerChild setting, "
                         "consider raising the MaxThreadsPerChild or "
                         "NumServers settings");
ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxClients of %d would require %d servers and "
                         "exceed ServerLimit of %d, decreasing to %d",
                         max_clients, ap_daemons_limit, server_limit,
                         server_limit * threads_per_child);
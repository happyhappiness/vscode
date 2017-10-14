ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxClients of %d is not an integer multiple of "
                         "ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d", max_clients, threads_per_child,
                         tmp_max_clients);
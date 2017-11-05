ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "MaxClients of %d is less than ThreadsPerChild "
                         "of %d, increasing to match",
                         max_clients, threads_per_child);
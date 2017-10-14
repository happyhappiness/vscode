ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00317)
                         "MaxRequestWorkers of %d is not an integer multiple of "
                         "ThreadsPerChild of %d, decreasing to nearest "
                         "multiple %d", max_workers, threads_per_child,
                         tmp_max_workers);
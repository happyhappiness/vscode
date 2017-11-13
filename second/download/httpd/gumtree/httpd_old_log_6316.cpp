ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00318)
                         "WARNING: MaxRequestWorkers of %d would require %d "
                         "servers and ", max_workers, ap_daemons_limit);
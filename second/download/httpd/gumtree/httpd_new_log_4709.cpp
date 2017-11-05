ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS,
                             ap_server_conf, APLOGNO(00362)
                             "Child: Waiting %d more seconds "
                             "for %d worker threads to finish.",
                             time_remains / 1000, threads_created);
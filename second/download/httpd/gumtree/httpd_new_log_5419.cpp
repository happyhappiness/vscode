ap_log_error(APLOG_MARK, APLOG_NOTICE,
                             0, ap_server_conf, APLOGNO(00051)
                             "child pid %ld exit signal %s (%d), "
                             "possible coredump in %s",
                             (long)pid->pid, sigdesc, signum,
                             ap_coredump_dir);
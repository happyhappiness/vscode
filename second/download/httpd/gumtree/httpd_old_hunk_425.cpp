    apr_socket_close(listening_sockets[0]);

    if ((one_process || shutdown_pending) && !child_fatal) {
        const char *pidfile = NULL;
        pidfile = ap_server_root_relative (pconf, ap_pid_fname);
        if ( pidfile != NULL && unlink(pidfile) == 0)
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, ap_server_conf,
                         "removed PID file %s (pid=%ld)", pidfile, 
                         (long)getpid());
    }

    if (one_process) {
        return 1;

    apr_status_t status=0;

    pconf = _pconf;
    ap_server_conf = s;

    if (setup_listeners(s)) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ALERT, status, s,
            "no listening sockets available, shutting down");
        return -1;
    }

    restart_pending = shutdown_pending = 0;
    worker_thread_count = 0;
    apr_thread_mutex_create(&worker_thread_count_mutex, APR_THREAD_MUTEX_DEFAULT, pconf);
    apr_thread_mutex_create(&accept_mutex, APR_THREAD_MUTEX_DEFAULT, pconf);

    if (!is_graceful) {
        if (ap_run_pre_mpm(s->process->pool, SB_NOT_SHARED) != OK) {
            return 1;
        }

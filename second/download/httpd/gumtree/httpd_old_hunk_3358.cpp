    apr_status_t status=0;

    pconf = _pconf;
    ap_server_conf = s;

    if (setup_listeners(s)) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, status, s,
            "no listening sockets available, shutting down");
        return -1;
    }

    restart_pending = shutdown_pending = 0;
    worker_thread_count = 0;

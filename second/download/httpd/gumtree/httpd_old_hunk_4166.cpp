    pconf = _pconf;
    ap_server_conf = s;

    if (setup_listeners(s)) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, status, s, APLOGNO(00223)
            "no listening sockets available, shutting down");
        return -1;
    }

    restart_pending = shutdown_pending = 0;
    worker_thread_count = 0;

    if (!is_graceful) {
        if (ap_run_pre_mpm(s->process->pool, SB_NOT_SHARED) != OK) {
            return 1;
        }
    }

    /* Only set slot 0 since that is all NetWare will ever have. */
    ap_scoreboard_image->parent[0].pid = getpid();
    ap_run_child_status(ap_server_conf,

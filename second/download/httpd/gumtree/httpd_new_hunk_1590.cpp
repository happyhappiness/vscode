    }
    worker->s = (proxy_worker_stat *)score;
    /*
     * recheck to see if we've already been here. Possible
     * if proxy is using scoreboard to hold shared stats
     */
    if (PROXY_WORKER_IS_INITIALIZED(worker)) {
        /* The worker share is already initialized */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: worker %s already initialized",
              worker->name);
        return;
    }

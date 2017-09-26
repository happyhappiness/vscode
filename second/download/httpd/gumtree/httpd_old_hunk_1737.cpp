#if PROXY_HAS_SCOREBOARD
    lb_score *score = NULL;
#else
    void *score = NULL;
#endif

    if (worker->s && PROXY_WORKER_IS_INITIALIZED(worker)) {
        /* The worker share is already initialized */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: worker %s already initialized",
              worker->name);
        return;
    }

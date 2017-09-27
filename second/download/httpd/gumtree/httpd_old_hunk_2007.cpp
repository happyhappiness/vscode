#if PROXY_HAS_SCOREBOARD
    lb_score *score = NULL;
#else
    void *score = NULL;
#endif

    if (worker->s && (worker->s->status & PROXY_WORKER_INITIALIZED)) {
        /* The worker share is already initialized */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: worker %s already initialized",
              worker->name);
        return;
    }

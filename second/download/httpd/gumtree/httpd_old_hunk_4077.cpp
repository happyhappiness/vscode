    if (idle_secs <= 0) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, workers->s,
                     APLOGNO(02962) "h2_workers: max_worker_idle_sec value of %d"
                     " is not valid, ignored.", idle_secs);
        return;
    }
    apr_atomic_set32(&workers->max_idle_secs, idle_secs);
}


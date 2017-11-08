static int
simple_check_config(apr_pool_t * p, apr_pool_t * plog,
                    apr_pool_t * ptemp, server_rec * s)
{
    simple_core_t *sc = simple_core_get();

    if (sc->procmgr.proc_count > SIMPLE_MAX_PROC) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "simple_check_config: SimpleProcCount must be at most %d",
                     SIMPLE_MAX_PROC);
        return !OK;
    }

    if (sc->procmgr.proc_count < SIMPLE_MIN_PROC) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "simple_check_config: SimpleProcCount must be at least %d",
                     SIMPLE_MIN_PROC);
        return !OK;
    }

    if (sc->procmgr.thread_count > SIMPLE_MAX_THREADS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "simple_check_config: SimpleThreadCount must be at most %d",
                     SIMPLE_MAX_THREADS);
        return !OK;
    }

    if (sc->procmgr.thread_count < SIMPLE_MIN_THREADS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "simple_check_config: SimpleThreadCount must be at least %d",
                     SIMPLE_MIN_THREADS);
        return !OK;
    }

    return OK;
}
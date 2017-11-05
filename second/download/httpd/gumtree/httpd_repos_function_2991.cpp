static int simple_query(int query_code, int *result, apr_status_t *rv)
{
    simple_core_t *sc = simple_core_get();

    *rv = APR_SUCCESS;
    switch (query_code) {
    case AP_MPMQ_IS_THREADED:
        *result = AP_MPMQ_STATIC;
        break;
    case AP_MPMQ_IS_FORKED:
        *result = AP_MPMQ_DYNAMIC;
        break;
    case AP_MPMQ_IS_ASYNC:
        *result = 1;
        break;
    case AP_MPMQ_MAX_DAEMON_USED:
        *result = sc->procmgr.proc_count;
        break;
    case AP_MPMQ_HARD_LIMIT_DAEMONS:
        *result = sc->procmgr.proc_count;
        break;
    case AP_MPMQ_HARD_LIMIT_THREADS:
        *result = sc->procmgr.thread_count;
        break;
    case AP_MPMQ_MAX_THREADS:
        *result = sc->procmgr.thread_count;
        break;
    case AP_MPMQ_MAX_SPARE_DAEMONS:
        *result = sc->procmgr.proc_count;
        break;
    case AP_MPMQ_MIN_SPARE_DAEMONS:
        *result = sc->procmgr.proc_count;
        break;
    case AP_MPMQ_MIN_SPARE_THREADS:
    case AP_MPMQ_MAX_SPARE_THREADS:
        *result = sc->procmgr.thread_count;
        break;
    case AP_MPMQ_MAX_REQUESTS_DAEMON:
        *result = sc->procmgr.max_requests_per_child;
        break;
    case AP_MPMQ_MAX_DAEMONS:
        *result = sc->procmgr.proc_count;
        break;
    case AP_MPMQ_MPM_STATE:
        *result = sc->mpm_state;
        break;
    case AP_MPMQ_GENERATION:
        *result = 0;
        break;
    default:
        *rv = APR_ENOTIMPL;
        break;
    }
    return OK;
}
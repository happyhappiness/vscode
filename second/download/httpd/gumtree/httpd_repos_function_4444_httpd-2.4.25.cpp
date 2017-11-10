static int worker_query(int query_code, int *result, apr_status_t *rv)
{
    *rv = APR_SUCCESS;
    switch (query_code) {
        case AP_MPMQ_MAX_DAEMON_USED:
            *result = retained->max_daemons_limit;
            break;
        case AP_MPMQ_IS_THREADED:
            *result = AP_MPMQ_STATIC;
            break;
        case AP_MPMQ_IS_FORKED:
            *result = AP_MPMQ_DYNAMIC;
            break;
        case AP_MPMQ_HARD_LIMIT_DAEMONS:
            *result = server_limit;
            break;
        case AP_MPMQ_HARD_LIMIT_THREADS:
            *result = thread_limit;
            break;
        case AP_MPMQ_MAX_THREADS:
            *result = threads_per_child;
            break;
        case AP_MPMQ_MIN_SPARE_DAEMONS:
            *result = 0;
            break;
        case AP_MPMQ_MIN_SPARE_THREADS:
            *result = min_spare_threads;
            break;
        case AP_MPMQ_MAX_SPARE_DAEMONS:
            *result = 0;
            break;
        case AP_MPMQ_MAX_SPARE_THREADS:
            *result = max_spare_threads;
            break;
        case AP_MPMQ_MAX_REQUESTS_DAEMON:
            *result = ap_max_requests_per_child;
            break;
        case AP_MPMQ_MAX_DAEMONS:
            *result = ap_daemons_limit;
            break;
        case AP_MPMQ_MPM_STATE:
            *result = mpm_state;
            break;
        case AP_MPMQ_GENERATION:
            *result = retained->my_generation;
            break;
        default:
            *rv = APR_ENOTIMPL;
            break;
    }
    return OK;
}
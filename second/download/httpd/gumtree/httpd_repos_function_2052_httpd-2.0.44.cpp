static int netware_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    int debug;
    char *addrname = NULL;

    debug = ap_exists_config_define("DEBUG");

    is_graceful = 0;
    ap_my_pid = getpid();
    addrname = getaddressspacename (NULL, NULL);
    if (addrname) {
        ap_my_addrspace = apr_pstrdup (p, addrname);
        free (addrname);
    }

    ap_listen_pre_config();
    ap_threads_to_start = DEFAULT_START_THREADS;
    ap_threads_min_free = DEFAULT_MIN_FREE_THREADS;
    ap_threads_max_free = DEFAULT_MAX_FREE_THREADS;
    ap_threads_limit = HARD_THREAD_LIMIT;
    ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
    ap_extended_status = 0;

    return OK;
}
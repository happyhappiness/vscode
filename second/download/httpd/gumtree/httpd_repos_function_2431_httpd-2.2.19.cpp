static int netware_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    int debug;
    char *addrname = NULL;

    mpm_state = AP_MPMQ_STARTING;

    debug = ap_exists_config_define("DEBUG");

    is_graceful = 0;
    ap_my_pid = getpid();
    addrname = getaddressspacename (NULL, NULL);
    if (addrname) {
        ap_my_addrspace = apr_pstrdup (p, addrname);
        free (addrname);
    }

#ifndef USE_WINSOCK
    /* The following call has been moved to the mod_nw_ssl pre-config handler */
    ap_listen_pre_config();
#endif

    ap_threads_to_start = DEFAULT_START_THREADS;
    ap_threads_min_free = DEFAULT_MIN_FREE_THREADS;
    ap_threads_max_free = DEFAULT_MAX_FREE_THREADS;
    ap_threads_limit = HARD_THREAD_LIMIT;
    ap_max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;
    ap_extended_status = 0;
    ap_thread_stacksize = DEFAULT_THREAD_STACKSIZE;
#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
    ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
#endif

    return OK;
}
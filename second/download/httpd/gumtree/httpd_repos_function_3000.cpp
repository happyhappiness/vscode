apr_status_t simple_core_init_once(void)
{
    apr_status_t rv;
    const char *userdata_key = "mpm_simple_module";
    simple_core_t *sc;

    g_simple_core = ap_retained_data_get(userdata_key);
    if (g_simple_core) {
        return APR_SUCCESS;
    }
    
    sc = g_simple_core = ap_retained_data_create(userdata_key, sizeof(*g_simple_core));

    apr_pool_create(&sc->pool, ap_pglobal);

    apr_pool_tag(sc->pool, "simple-mpm-core");

    sc->mpm_state = AP_MPMQ_STARTING;
    sc->procmgr.proc_count = SIMPLE_DEF_PROC;
    sc->procmgr.thread_count = SIMPLE_DEF_THREADS;
    sc->procmgr.max_requests_per_child = DEFAULT_MAX_REQUESTS_PER_CHILD;

    sc->children = apr_hash_make(sc->pool);
    /* TODO: configurable spawning mech */
    sc->spawn_via = SIMPLE_SPAWN_FORK;

    APR_RING_INIT(&sc->timer_ring, simple_timer_t, link);

    rv = apr_thread_mutex_create(&sc->mtx, 0, sc->pool);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_core_init_once: apr_thread_mutex_create failed.");
        return rv;
    }

    return APR_SUCCESS;
}
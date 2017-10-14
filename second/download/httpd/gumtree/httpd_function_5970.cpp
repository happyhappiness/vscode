apr_status_t h2_conn_child_init(apr_pool_t *pool, server_rec *s)
{
    const h2_config *config = h2_config_sget(s);
    apr_status_t status = APR_SUCCESS;
    int minw = h2_config_geti(config, H2_CONF_MIN_WORKERS);
    int maxw = h2_config_geti(config, H2_CONF_MAX_WORKERS);
    
    int max_threads_per_child = 0;
    int threads_limit = 0;
    int idle_secs = 0;
    int i;

    h2_config_init(pool);
    
    ap_mpm_query(AP_MPMQ_MAX_THREADS, &max_threads_per_child);
    ap_mpm_query(AP_MPMQ_HARD_LIMIT_THREADS, &threads_limit);
    
    for (i = 0; ap_loaded_modules[i]; ++i) {
        module *m = ap_loaded_modules[i];
        if (!strcmp("event.c", m->name)) {
            mpm_type = H2_MPM_EVENT;
            mpm_module = m;
        }
        else if (!strcmp("worker.c", m->name)) {
            mpm_type = H2_MPM_WORKER;
            mpm_module = m;
        }
        else if (!strcmp("prefork.c", m->name)) {
            mpm_type = H2_MPM_PREFORK;
            mpm_module = m;
        }
    }
    
    if (minw <= 0) {
        minw = max_threads_per_child;
    }
    if (maxw <= 0) {
        maxw = threads_limit;
        if (maxw < minw) {
            maxw = minw;
        }
    }
    
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "h2_workers: min=%d max=%d, mthrpchild=%d, thr_limit=%d", 
                 minw, maxw, max_threads_per_child, threads_limit);
    
    workers = h2_workers_create(s, pool, minw, maxw);
    idle_secs = h2_config_geti(config, H2_CONF_MAX_WORKER_IDLE_SECS);
    h2_workers_set_max_idle_secs(workers, idle_secs);
    
    return status;
}
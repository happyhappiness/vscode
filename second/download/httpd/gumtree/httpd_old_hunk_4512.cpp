    minw = h2_config_geti(config, H2_CONF_MIN_WORKERS);
    maxw = h2_config_geti(config, H2_CONF_MAX_WORKERS);    
    if (minw <= 0) {
        minw = max_threads_per_child;
    }
    if (maxw <= 0) {
        maxw = minw;
    }
    
    /* How many file handles is it safe to use for transfer
     * to the master connection to be streamed out? 
     * Is there a portable APR rlimit on NOFILES? Have not
     * found it. And if, how many of those would we set aside?
     * This leads all into a process wide handle allocation strategy
     * which ultimately would limit the number of accepted connections
     * with the assumption of implicitly reserving n handles for every 
     * connection and requiring modules with excessive needs to allocate
     * from a central pool.
     */
    n = h2_config_geti(config, H2_CONF_SESSION_FILES);
    if (n < 0) {
        max_tx_handles = maxw * 2;
    }
    else {
        max_tx_handles = maxw * n;
    }
    
    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                 "h2_workers: min=%d max=%d, mthrpchild=%d, tx_files=%d", 
                 minw, maxw, max_threads_per_child, max_tx_handles);
    workers = h2_workers_create(s, pool, minw, maxw, max_tx_handles);
    
    idle_secs = h2_config_geti(config, H2_CONF_MAX_WORKER_IDLE_SECS);
    h2_workers_set_max_idle_secs(workers, idle_secs);
 
    ap_register_input_filter("H2_IN", h2_filter_core_input,
                             NULL, AP_FTYPE_CONNECTION);
   
    status = h2_mplx_child_init(pool, s);


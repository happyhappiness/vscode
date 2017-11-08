void h2_config_init(apr_pool_t *pool) {
    /* Determine a good default for this platform and mpm?
     * TODO: not sure how APR wants to hand out this piece of 
     * information.
     */
    int max_files = 256;
    int conn_threads = 1;
    int tx_files = max_files / 4;
    
    (void)pool;
    ap_mpm_query(AP_MPMQ_MAX_THREADS, &conn_threads);
    switch (h2_conn_mpm_type()) {
        case H2_MPM_PREFORK:
        case H2_MPM_WORKER:
        case H2_MPM_EVENT:
            /* allow that many transfer open files per mplx */
            files_per_session = (tx_files / conn_threads);
            break;
        default:
            /* don't know anything about it, stay safe */
            break;
    }
}
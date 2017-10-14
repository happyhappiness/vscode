apr_status_t h2_conn_setup(h2_task_env *env, struct h2_worker *worker)
{
    conn_rec *master = env->mplx->c;
    
    ap_log_perror(APLOG_MARK, APLOG_TRACE3, 0, env->pool,
                  "h2_conn(%ld): created from master", master->id);
    
    /* Ok, we are just about to start processing the connection and
     * the worker is calling us to setup all necessary resources.
     * We can borrow some from the worker itself and some we do as
     * sub-resources from it, so that we get a nice reuse of
     * pools.
     */
    env->c.pool = env->pool;
    env->c.bucket_alloc = h2_worker_get_bucket_alloc(worker);
    env->c.current_thread = h2_worker_get_thread(worker);
    
    env->c.conn_config = ap_create_conn_config(env->pool);
    env->c.notes = apr_table_make(env->pool, 5);
    
    ap_set_module_config(env->c.conn_config, &core_module, 
                         h2_worker_get_socket(worker));
    
    /* If we serve http:// requests over a TLS connection, we do
     * not want any mod_ssl vars to be visible.
     */
    if (ssl_module && (!env->scheme || strcmp("http", env->scheme))) {
        /* See #19, there is a range of SSL variables to be gotten from
         * the main connection that should be available in request handlers
         */
        void *sslcfg = ap_get_module_config(master->conn_config, ssl_module);
        if (sslcfg) {
            ap_set_module_config(env->c.conn_config, ssl_module, sslcfg);
        }
    }
    
    /* This works for mpm_worker so far. Other mpm modules have 
     * different needs, unfortunately. The most interesting one 
     * being mpm_event...
     */
    switch (h2_conn_mpm_type()) {
        case H2_MPM_WORKER:
            /* all fine */
            break;
        case H2_MPM_EVENT: 
            fix_event_conn(&env->c, master);
            break;
        default:
            /* fingers crossed */
            break;
    }
    
    /* TODO: we simulate that we had already a request on this connection.
     * This keeps the mod_ssl SNI vs. Host name matcher from answering 
     * 400 Bad Request
     * when names do not match. We prefer a predictable 421 status.
     */
    env->c.keepalives = 1;
    
    return APR_SUCCESS;
}
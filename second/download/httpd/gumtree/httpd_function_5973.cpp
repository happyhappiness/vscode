apr_status_t h2_conn_setup(h2_task *task, apr_bucket_alloc_t *bucket_alloc,
                           apr_thread_t *thread, apr_socket_t *socket)
{
    conn_rec *master = task->mplx->c;
    
    ap_log_perror(APLOG_MARK, APLOG_TRACE3, 0, task->pool,
                  "h2_conn(%ld): created from master", master->id);
    
    /* Ok, we are just about to start processing the connection and
     * the worker is calling us to setup all necessary resources.
     * We can borrow some from the worker itself and some we do as
     * sub-resources from it, so that we get a nice reuse of
     * pools.
     */
    task->c->pool = task->pool;
    task->c->current_thread = thread;
    task->c->bucket_alloc = bucket_alloc;
    
    task->c->conn_config = ap_create_conn_config(task->pool);
    task->c->notes = apr_table_make(task->pool, 5);
    
    /* In order to do this in 2.4.x, we need to add a member to conn_rec */
    task->c->master = master;
    
    ap_set_module_config(task->c->conn_config, &core_module, socket);
    
    /* This works for mpm_worker so far. Other mpm modules have 
     * different needs, unfortunately. The most interesting one 
     * being mpm_event...
     */
    switch (h2_conn_mpm_type()) {
        case H2_MPM_WORKER:
            /* all fine */
            break;
        case H2_MPM_EVENT: 
            fix_event_conn(task->c, master);
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
    task->c->keepalives = 1;
    
    return APR_SUCCESS;
}
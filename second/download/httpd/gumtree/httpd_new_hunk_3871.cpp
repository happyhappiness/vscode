
static module *h2_conn_mpm_module(void) {
    check_modules();
    return mpm_module;
}

apr_status_t h2_conn_process(conn_rec *c, request_rec *r, server_rec *s)
{
    apr_status_t status;
    h2_session *session;
    const h2_config *config;
    int rv;
    
    if (!workers) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02911) 
                      "workers not initialized");
        return APR_EGENERAL;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, "h2_conn_process start");
    
    if (!s && r) {
        s = r->server;
    }
    
    config = s? h2_config_sget(s) : h2_config_get(c);
    if (r) {
        session = h2_session_rcreate(r, config, workers);
    }
    else {
        session = h2_session_create(c, config, workers);
    }
    
    if (!h2_is_acceptable_connection(c, 1)) {
        nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 0,
                              NGHTTP2_INADEQUATE_SECURITY, NULL, 0);
    } 

    ap_update_child_status_from_conn(c->sbh, SERVER_BUSY_READ, c);
    status = h2_session_start(session, &rv);
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session(%ld): starting on %s:%d", session->id,
                  session->c->base_server->server_hostname,
                  session->c->local_addr->port);
    if (status != APR_SUCCESS) {
        h2_session_abort(session, status, rv);
        h2_session_eoc_callback(session);
        return status;
    }
    
    status = h2_session_process(session);

    ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session(%ld): done", session->id);
    /* Make sure this connection gets closed properly. */
    ap_update_child_status_from_conn(c->sbh, SERVER_CLOSING, c);
    c->keepalive = AP_CONN_CLOSE;
    if (c->cs) {
        c->cs->state = CONN_STATE_WRITE_COMPLETION;
    }

    h2_session_close(session);
    /* hereafter session will be gone */
    return status;
}


static void fix_event_conn(conn_rec *c, conn_rec *master);

conn_rec *h2_conn_create(conn_rec *master, apr_pool_t *pool)
{
    conn_rec *c;
    
    AP_DEBUG_ASSERT(master);

    /* This is like the slave connection creation from 2.5-DEV. A
     * very efficient way - not sure how compatible this is, since
     * the core hooks are no longer run.
     * But maybe it's is better this way, not sure yet.
     */
    c = (conn_rec *) apr_palloc(pool, sizeof(conn_rec));
    if (c == NULL) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, pool, 
                      APLOGNO(02913) "h2_task: creating conn");
        return NULL;
    }
    
    memcpy(c, master, sizeof(conn_rec));
    c->id = (master->id & (long)pool);
    c->master = master;
    c->input_filters = NULL;
    c->output_filters = NULL;
    c->pool = pool;        
    return c;
}

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

/* This is an internal mpm event.c struct which is disguised
 * as a conn_state_t so that mpm_event can have special connection

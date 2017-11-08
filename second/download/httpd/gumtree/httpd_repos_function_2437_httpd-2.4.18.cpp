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
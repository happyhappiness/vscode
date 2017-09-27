    if (status == APR_SUCCESS) {
        return DONE; /* This is the same, right? */
    }
    return status;
}

conn_rec *h2_slave_create(conn_rec *master, int slave_id, apr_pool_t *parent)
{
    apr_allocator_t *allocator;
    apr_pool_t *pool;
    conn_rec *c;
    void *cfg;
    
    ap_assert(master);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, master,
                  "h2_conn(%ld): create slave", master->id);
    
    /* We create a pool with its own allocator to be used for
     * processing a request. This is the only way to have the processing
     * independant of its parent pool in the sense that it can work in
     * another thread.
     */
    apr_allocator_create(&allocator);
    apr_pool_create_ex(&pool, parent, NULL, allocator);
    apr_pool_tag(pool, "h2_slave_conn");
    apr_allocator_owner_set(allocator, pool);

    c = (conn_rec *) apr_palloc(pool, sizeof(conn_rec));
    if (c == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, master, 
                      APLOGNO(02913) "h2_task: creating conn");
        return NULL;
    }
    
    memcpy(c, master, sizeof(conn_rec));
        
    c->master                 = master;
    c->pool                   = pool;   
    c->conn_config            = ap_create_conn_config(pool);
    c->notes                  = apr_table_make(pool, 5);
    c->input_filters          = NULL;
    c->output_filters         = NULL;
    c->bucket_alloc           = apr_bucket_alloc_create(pool);
    c->data_in_input_filters  = 0;
    c->data_in_output_filters = 0;
    c->clogging_input_filters = 1;
    c->log                    = NULL;
    c->log_id                 = apr_psprintf(pool, "%ld-%d", 
                                             master->id, slave_id);
    /* Simulate that we had already a request on this connection. */
    c->keepalives             = 1;
    /* We cannot install the master connection socket on the slaves, as
     * modules mess with timeouts/blocking of the socket, with
     * unwanted side effects to the master connection processing.
     * Fortunately, since we never use the slave socket, we can just install

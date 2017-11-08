conn_rec *h2_conn_create(conn_rec *master, apr_pool_t *pool)
{
    apr_socket_t *socket;
    conn_rec *c;
    
    AP_DEBUG_ASSERT(master);
    
    /* CAVEAT: it seems necessary to setup the conn_rec in the master
     * connection thread. Other attempts crashed. 
     * HOWEVER: we setup the connection using the pools and other items
     * from the master connection, since we do not want to allocate 
     * lots of resources here. 
     * Lets allocated pools and everything else when we actually start
     * working on this new connection.
     */
    /* Not sure about the scoreboard handle. Reusing the one from the main
     * connection could make sense, is not really correct, but we cannot
     * easily create new handles for our worker threads either.
     * TODO
     */
    socket = ap_get_module_config(master->conn_config, &core_module);
    c = ap_run_create_connection(pool, master->base_server,
                                 socket,
                                 master->id^((long)pool), 
                                 master->sbh,
                                 master->bucket_alloc);
    if (c == NULL) {
        ap_log_perror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, pool, 
                      APLOGNO(02913) "h2_task: creating conn");
        return NULL;
    }
    return c;
}
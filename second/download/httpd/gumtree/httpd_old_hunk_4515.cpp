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
     * a single, process-wide dummy and everyone is happy.
     */
    ap_set_module_config(c->conn_config, &core_module, dummy_socket);
    /* TODO: these should be unique to this thread */
    c->sbh                    = master->sbh;
    /* TODO: not all mpm modules have learned about slave connections yet.
     * copy their config from master to slave.
     */
    if (h2_conn_mpm_module()) {
        cfg = ap_get_module_config(master->conn_config, h2_conn_mpm_module());
        ap_set_module_config(c->conn_config, h2_conn_mpm_module(), cfg);
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, 
                  "h2_task: creating conn, master=%ld, sid=%ld, logid=%s", 
                  master->id, c->id, c->log_id);
    return c;
}

void h2_slave_destroy(conn_rec *slave)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, slave,
                  "h2_slave_conn(%ld): destroy (task=%s)", slave->id,
                  apr_table_get(slave->notes, H2_TASK_ID_NOTE));
    apr_pool_destroy(slave->pool);
}

apr_status_t h2_slave_run_pre_connection(conn_rec *slave, apr_socket_t *csd)
{
    return ap_run_pre_connection(slave, csd);

     */
    if (h2_conn_mpm_module()) {
        cfg = ap_get_module_config(master->conn_config, h2_conn_mpm_module());
        ap_set_module_config(c->conn_config, h2_conn_mpm_module(), cfg);
    }

    return c;
}

void h2_slave_destroy(conn_rec *slave, apr_allocator_t **pallocator)
{
    apr_pool_t *parent;
    apr_allocator_t *allocator = apr_pool_allocator_get(slave->pool);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, slave,
                  "h2_slave_conn(%ld): destroy (task=%s)", slave->id,
                  apr_table_get(slave->notes, H2_TASK_ID_NOTE));
    /* Attache the allocator to the parent pool and return it for
     * reuse, otherwise the own is still the slave pool and it will
     * get destroyed with it. */
    parent = apr_pool_parent_get(slave->pool);
    if (pallocator && parent) {
        apr_allocator_owner_set(allocator, parent);
        *pallocator = allocator;
    }
    apr_pool_destroy(slave->pool);
}

apr_status_t h2_slave_run_pre_connection(conn_rec *slave, apr_socket_t *csd)
{
    return ap_run_pre_connection(slave, csd);

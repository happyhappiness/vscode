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
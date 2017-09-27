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

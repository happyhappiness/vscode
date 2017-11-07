static int h2_task_pre_conn(conn_rec* c, void *arg)
{
    
    h2_ctx *ctx = h2_ctx_get(c);
    
    (void)arg;
    if (h2_ctx_is_task(ctx)) {
        h2_task *task = h2_ctx_get_task(ctx);
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                      "h2_h2, pre_connection, found stream task");
        
        /* Add our own, network level in- and output filters.
         */
        ap_add_input_filter("H2_TO_H1", task, NULL, c);
        ap_add_output_filter("H1_TO_H2", task, NULL, c);
    }
    return OK;
}
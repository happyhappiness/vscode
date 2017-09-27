     * content handlers that have the ability to grok HTTP and do their
     * own access checking, etc (e.g. servlet engines).
     *
     * Use this hook with extreme care and only if you know what you are
     * doing.
     */
    if (ap_extended_status)
        ap_time_process_request(r->connection->sbh, START_PREQUEST);
    access_status = ap_run_quick_handler(r, 0);  /* Not a look-up request */
    if (access_status == DECLINED) {
        access_status = ap_process_request_internal(r);
        if (access_status == OK) {
            access_status = ap_invoke_handler(r);
        }
    }

    ap_die_r(access_status, r, HTTP_OK);

    /*
     * We want to flush the last packet if this isn't a pipelining connection
     * *before* we start into logging.  Suppose that the logging causes a DNS
     * lookup to occur, which may have a high latency.  If we hold off on
     * this packet, then it'll appear like the link is stalled when really
     * it's the application that's stalled.
     */
    check_pipeline_flush(r);
    ap_update_child_status(r->connection->sbh, SERVER_BUSY_LOG, r);
    ap_run_log_transaction(r);
    if (ap_extended_status)
        ap_time_process_request(r->connection->sbh, STOP_PREQUEST);
}

static apr_table_t *rename_original_env(apr_pool_t *p, apr_table_t *t)
{
    const apr_array_header_t *env_arr = apr_table_elts(t);
    const apr_table_entry_t *elts = (const apr_table_entry_t *) env_arr->elts;

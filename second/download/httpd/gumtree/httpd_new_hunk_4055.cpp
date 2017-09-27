/*******************************************************************************
 * Once per lifetime init, retrieve optional functions
 */
apr_status_t h2_switch_init(apr_pool_t *pool, server_rec *s)
{
    (void)pool;
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s, "h2_switch init");

    return APR_SUCCESS;
}

static int h2_protocol_propose(conn_rec *c, request_rec *r,
                               server_rec *s,

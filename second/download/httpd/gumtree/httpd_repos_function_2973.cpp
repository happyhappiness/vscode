static void simple_io_timeout_cb(simple_core_t * sc, void *baton)
{
    simple_conn_t *scon = (simple_conn_t *) baton;
    /* pqXXXXX: handle timeouts. */
    conn_rec *c = scon->c;
    conn_state_t *cs = c->cs;

    cs = NULL;

    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                 "io timeout hit (?)");
}
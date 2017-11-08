static void *simple_io_setup_conn(apr_thread_t * thread, void *baton)
{
    apr_status_t rv;
    ap_sb_handle_t *sbh;
    conn_state_t *cs;
    long conn_id = 0;
    simple_sb_t *sb;
    simple_conn_t *scon = (simple_conn_t *) baton;

    /* pqXXXXX: remove this. */
    ap_create_sb_handle(&sbh, scon->pool, 0, 0);

    scon->ba = apr_bucket_alloc_create(scon->pool);

    scon->c = ap_run_create_connection(scon->pool, ap_server_conf, scon->sock,
                                       conn_id, sbh, scon->ba);

    scon->c->cs = apr_pcalloc(scon->pool, sizeof(conn_state_t));
    cs = scon->c->cs;
    sb = apr_pcalloc(scon->pool, sizeof(simple_sb_t));

    scon->c->current_thread = thread;

    cs->pfd.p = scon->pool;
    cs->pfd.desc_type = APR_POLL_SOCKET;
    cs->pfd.desc.s = scon->sock;
    cs->pfd.reqevents = APR_POLLIN;

    sb->type = SIMPLE_PT_CORE_IO;
    sb->baton = scon;
    cs->pfd.client_data = sb;

    ap_update_vhost_given_ip(scon->c);

    rv = ap_run_pre_connection(scon->c, scon->sock);
    if (rv != OK && rv != DONE) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                     "simple_io_setup_conn: connection aborted");
        scon->c->aborted = 1;
    }

    scon->c->cs->state = CONN_STATE_READ_REQUEST_LINE;

    rv = simple_io_process(scon);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf,
                     "simple_io_setup_conn: simple_io_process failed (?)");
    }

    return NULL;
}
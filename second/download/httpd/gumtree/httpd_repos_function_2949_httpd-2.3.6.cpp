static void *simple_io_invoke(apr_thread_t * thread, void *baton)
{
    simple_sb_t *sb = (simple_sb_t *) baton;
    simple_conn_t *scon = (simple_conn_t *) sb->baton;
    apr_status_t rv;

    scon->c->current_thread = thread;

    rv = simple_io_process(scon);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf,
                     "simple_io_invoke: simple_io_process failed (?)");
    }

    return NULL;
}
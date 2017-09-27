
    if (!shutdown_in_progress) {
        /* Yow, hit an irrecoverable error! Tell the child to die. */
        SetEvent(exit_event);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00348)
                 "Child: Accept thread exiting.");
    return 0;
}


static winnt_conn_ctx_t *winnt_get_connection(winnt_conn_ctx_t *context)
{

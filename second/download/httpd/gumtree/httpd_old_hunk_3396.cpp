
    if (!shutdown_in_progress) {
        /* Yow, hit an irrecoverable error! Tell the child to die. */
        SetEvent(exit_event);
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, ap_server_conf,
                 "Child %d: Accept thread exiting.", my_pid);
    return 0;
}


static winnt_conn_ctx_t *winnt_get_connection(winnt_conn_ctx_t *context)
{

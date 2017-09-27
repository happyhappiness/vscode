            || !strcasecmp(signal_arg, "config")) {
        return OK;
    }

    if (ap_setup_listeners(s) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0,
                     NULL, "no listening sockets available, shutting down");
        return DONE;
    }

    return OK;
}

static void winnt_child_init(apr_pool_t *pchild, struct server_rec *s)
{
    apr_status_t rv;

    setup_signal_names(apr_psprintf(pchild,"ap%d", parent_pid));

    /* This is a child process, not in single process mode */
    if (!one_process) {
        /* Set up events and the scoreboard */
        get_handles_from_parent(s, &exit_event, &start_mutex,
                                &ap_scoreboard_shm);

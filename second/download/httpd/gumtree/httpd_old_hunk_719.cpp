    if (ap_setup_listeners(s) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0, 
                     NULL, "no listening sockets available, shutting down");
        return DONE;
    }

    if (!set_listeners_noninheritable(s->process->pool)) {
        return 1;
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
        get_handles_from_parent(s);

        /* Set up the listeners */
        get_listeners_from_parent(s);

        ap_my_generation = ap_scoreboard_image->global->running_generation;
        rv = apr_proc_mutex_child_init(&start_mutex, signal_name_prefix, 
                                       s->process->pool);
    }
    else {
        /* Single process mode - this lock doesn't even need to exist */
        rv = apr_proc_mutex_create(&start_mutex, signal_name_prefix, 
                                   APR_LOCK_DEFAULT, s->process->pool);
        
        /* Borrow the shutdown_even as our _child_ loop exit event */
        exit_event = shutdown_event;
    }
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                     "%s child %d: Unable to init the start_mutex.",
                     service_name, my_pid);
        exit(APEXIT_CHILDINIT);
    }
}


AP_DECLARE(int) ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s )
{
    static int restart = 0;            /* Default is "not a restart" */

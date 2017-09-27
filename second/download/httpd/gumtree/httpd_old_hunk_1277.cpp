    ht = apr_hash_make(pchild);

    /* Initialize the child_events */
    max_requests_per_child_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!max_requests_per_child_event) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Child %d: Failed to create a max_requests event.", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    child_events[0] = exit_event;
    child_events[1] = max_requests_per_child_event;

    allowed_globals.jobsemaphore = CreateSemaphore(NULL, 0, 1000000, NULL);

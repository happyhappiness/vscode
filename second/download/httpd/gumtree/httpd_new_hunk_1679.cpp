        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                        "Parent: Unable to create child stdin pipe.");
        apr_pool_destroy(ptemp);
        return -1;
    }

    /* Create the child_ready_event */
    waitlist[waitlist_ready] = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!waitlist[waitlist_ready]) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Could not create ready event for child process");
        apr_pool_destroy (ptemp);

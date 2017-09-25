    bucket_alloc = apr_bucket_alloc_create(tpool);

    apr_poll_setup(&pollset, num_listensocks, tpool);
    for(lr = ap_listeners ; lr != NULL ; lr = lr->next)
        apr_poll_socket_add(pollset, lr->sd, APR_POLLIN);

    /* TODO: Switch to a system where threads reuse the results from earlier
       poll calls - manoj */
    is_listener = 0;
    while (!workers_may_exit) {

        ap_update_child_status_from_indexes(process_slot, thread_slot,
                                            SERVER_READY, NULL);
        if (!is_listener) {
            /* Wait until it's our turn to become the listener */
            if ((rv = worker_stack_wait(idle_worker_stack, my_worker_num)) !=
                APR_SUCCESS) {
                if (rv != APR_EINVAL) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                                 "worker_stack_wait failed. Shutting down");
                }
                break;

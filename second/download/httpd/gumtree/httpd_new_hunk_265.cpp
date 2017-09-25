    int is_idle = 0;

    free(ti);

    ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_STARTING, NULL);

    while (!workers_may_exit) {
        if (!is_idle) {
            rv = ap_queue_info_set_idle(worker_queue_info, last_ptrans);
            last_ptrans = NULL;
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,

    int thread_slot = ti->tid;
    apr_socket_t *csd = NULL;
    apr_bucket_alloc_t *bucket_alloc;
    apr_pool_t *last_ptrans = NULL;
    apr_pool_t *ptrans;                /* Pool for per-transaction stuff */
    apr_status_t rv;
    int is_idle = 0;

    free(ti);

    ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_STARTING, NULL);

    bucket_alloc = apr_bucket_alloc_create(apr_thread_pool_get(thd));

    while (!workers_may_exit) {
        if (!is_idle) {
            rv = ap_queue_info_set_idle(worker_queue_info, last_ptrans);
            last_ptrans = NULL;
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "ap_queue_info_set_idle failed. Attempting to "
                             "shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
                break;
            }
            is_idle = 1;
        }

        ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_READY, NULL);
worker_pop:
        if (workers_may_exit) {
            break;

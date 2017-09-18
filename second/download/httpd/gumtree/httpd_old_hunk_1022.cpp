    free(ti);

    ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_STARTING, NULL);

    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    apr_pool_create_ex(&ptrans, NULL, NULL, allocator);
    apr_allocator_owner_set(allocator, ptrans);

    /* XXX: What happens if this is allocated from the
     * single-thread-optimized ptrans pool? -aaron */
    bucket_alloc = apr_bucket_alloc_create(tpool);

    wakeup = (worker_wakeup_info *)apr_palloc(tpool, sizeof(*wakeup));
    wakeup->pool = ptrans;
    if ((rv = apr_thread_cond_create(&wakeup->cond, tpool)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "apr_thread_cond_create failed. Attempting to shutdown "

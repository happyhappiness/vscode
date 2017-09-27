        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "unable to open work queue, exiting");
        ap_scoreboard_image->servers[child_slot][thread_slot].tid = 0;
    }

    conn_id = ID_FROM_CHILD_THREAD(child_slot, thread_slot);
    ap_update_child_status_from_indexes(child_slot, thread_slot, SERVER_READY,
                                        NULL);

    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    bucket_alloc = apr_bucket_alloc_create_ex(allocator);


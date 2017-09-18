    }

    ap_update_child_status_from_indexes(0, child_slot, SERVER_DEAD, (request_rec*)NULL);

    apr_bucket_alloc_destroy(bucket_alloc);

    ap_log_error(APLOG_MARK, APLOG_NOTICE | APLOG_NOERRNO, 0, NULL,
                 "worker_thread %ld exiting", find_thread(NULL));
    
    apr_thread_mutex_lock(worker_thread_count_mutex);
    worker_thread_count--;
    apr_thread_mutex_unlock(worker_thread_count_mutex);


        if (score_idx) {
            ap_update_child_status_from_indexes(0, *score_idx,
                                                SERVER_DEAD, NULL);
        }
    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                 "Child %d: All worker threads have exited.", my_pid);

    CloseHandle(allowed_globals.jobsemaphore);
    apr_thread_mutex_destroy(allowed_globals.jobmutex);
    apr_thread_mutex_destroy(child_lock);

    if (use_acceptex) {

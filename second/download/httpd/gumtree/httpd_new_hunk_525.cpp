        }
        apr_thread_mutex_unlock(qlock);
    }

    /* Give busy worker threads a chance to service their connections */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Waiting for %d worker threads to exit.", my_pid, threads_created);
    end_time = time(NULL) + 180;
    while (threads_created) {
        rv = wait_for_many_objects(threads_created, child_handles, end_time - time(NULL));
        if (rv != WAIT_TIMEOUT) {
            rv = rv - WAIT_OBJECT_0;
            ap_assert((rv >= 0) && (rv < threads_created));
            cleanup_thread(child_handles, &threads_created, rv);
            continue;
        }
        break;
    }

    /* Kill remaining threads off the hard way */
    if (threads_created) {
        ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                     "Child %d: Terminating %d threads that failed to exit.", my_pid);
    }
    for (i = 0; i < threads_created; i++) {
        int *score_idx;
        TerminateThread(child_handles[i], 1);
        CloseHandle(child_handles[i]);
        /* Reset the scoreboard entry for the thread we just whacked */
        score_idx = apr_hash_get(ht, &child_handles[i], sizeof(thread));
        ap_update_child_status_from_indexes(0, *score_idx, SERVER_DEAD, NULL);        
    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: All worker threads have exited.", my_pid);

    CloseHandle(allowed_globals.jobsemaphore);
    apr_thread_mutex_destroy(allowed_globals.jobmutex);

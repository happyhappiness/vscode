    }

    /* 
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Starting %d worker threads.", my_pid, ap_threads_per_child);
    child_handles = (thread) apr_pcalloc(pchild, ap_threads_per_child * sizeof(int));
    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int *score_idx;
            int status = ap_scoreboard_image->servers[0][i].status;
            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
            }
            ap_update_child_status_from_indexes(0, i, SERVER_STARTING, NULL);
            child_handles[i] = (thread) _beginthreadex(NULL, 0, (LPTHREAD_START_ROUTINE) worker_main,
                                                       (void *) i, 0, &tid);
            if (child_handles[i] == 0) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                             "Child %d: _beginthreadex failed. Unable to create all worker threads. "
                             "Created %d of the %d threads requested with the ThreadsPerChild configuration directive.", 
                             threads_created, ap_threads_per_child);
                ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
                goto shutdown;
            }
            threads_created++;
            /* Save the score board index in ht keyed to the thread handle. We need this 
             * when cleaning up threads down below...
             */
            score_idx = apr_pcalloc(pchild, sizeof(int));
            *score_idx = i;
            apr_hash_set(ht, &child_handles[i], sizeof(thread), score_idx);
        }
        /* Start the listener only when workers are available */
        if (!listener_started && threads_created) {
            create_listener_thread();
            listener_started = 1;
        }
        if (threads_created == ap_threads_per_child) {
            break;
        }
        /* Check to see if the child has been told to exit */
        if (WaitForSingleObject(exit_event, 0) != WAIT_TIMEOUT) {
            break;
        }
        /* wait for previous generation to clean up an entry in the scoreboard */
        apr_sleep(1 * APR_USEC_PER_SEC);
    }

    /* Wait for one of three events:
     * exit_event: 
     *    The exit_event is signaled by the parent process to notify 
     *    the child that it is time to exit.

            closesocket(qhead->accept_socket);
            qhead = qhead->next;
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
                     "Child %d: Terminating %d threads that failed to exit.", 

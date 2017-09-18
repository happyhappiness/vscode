        }
        apr_thread_mutex_unlock(qlock);
    }

    /* Give busy worker threads a chance to service their connections */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Waiting for %d worker threads to exit.", my_pid, nthreads);
    end_time = time(NULL) + 180;
    while (nthreads) {
        rv = wait_for_many_objects(nthreads, child_handles, end_time - time(NULL));
        if (rv != WAIT_TIMEOUT) {
            rv = rv - WAIT_OBJECT_0;
            ap_assert((rv >= 0) && (rv < nthreads));
            cleanup_thread(child_handles, &nthreads, rv);
            continue;
        }
        break;
    }

    /* Kill remaining threads off the hard way */
    for (i = 0; i < nthreads; i++) {
        TerminateThread(child_handles[i], 1);
        CloseHandle(child_handles[i]);
    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: All worker threads have exited.", my_pid);

    CloseHandle(allowed_globals.jobsemaphore);
    apr_thread_mutex_destroy(allowed_globals.jobmutex);

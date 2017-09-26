            }
            ap_update_child_status_from_indexes(0, i, SERVER_STARTING, NULL);
            child_handles[i] = (HANDLE) _beginthreadex(NULL, (unsigned)ap_thread_stacksize,
                                                       worker_main, (void *) i, 0, &tid);
            if (child_handles[i] == 0) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                             "Child %d: _beginthreadex failed. Unable to create all worker threads. "
                             "Created %d of the %d threads requested with the ThreadsPerChild configuration directive.",
                             my_pid, threads_created, ap_threads_per_child);
                ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
                goto shutdown;
            }
            threads_created++;

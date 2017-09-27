                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                             "apr_thread_join: unable to join listener thread");
            }
        }
    }

    for (i = 0; i < ap_threads_per_child; i++) {
        if (threads[i]) { /* if we ever created this thread */
#ifdef HAVE_PTHREAD_KILL
            apr_os_thread_t *worker_os_thread;

            apr_os_thread_get(&worker_os_thread, threads[i]);
            pthread_kill(*worker_os_thread, WORKER_SIGNAL);

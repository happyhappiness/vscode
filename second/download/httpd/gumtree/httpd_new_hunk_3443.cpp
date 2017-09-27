            apr_os_thread_get(&worker_os_thread, threads[i]);
            pthread_kill(*worker_os_thread, WORKER_SIGNAL);
#endif

            rv = apr_thread_join(&thread_rv, threads[i]);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00278)
                             "apr_thread_join: unable to join worker "
                             "thread %d",
                             i);
            }
        }
    }

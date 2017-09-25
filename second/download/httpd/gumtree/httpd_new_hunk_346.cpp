    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: All worker threads have exited.", my_pid);

    CloseHandle(allowed_globals.jobsemaphore);
    apr_thread_mutex_destroy(allowed_globals.jobmutex);
    if (use_acceptex) {
    	apr_thread_mutex_destroy(qlock);
        CloseHandle(qwait_event);
    }

    apr_pool_destroy(pchild);
    CloseHandle(exit_event);

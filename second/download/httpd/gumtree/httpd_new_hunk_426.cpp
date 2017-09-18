      
        /* use ap_reclaim_child_processes starting with SIGTERM */
        ap_reclaim_child_processes(1);

        if (!child_fatal) {         /* already recorded */
            /* record the shutdown in the log */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                         "caught SIGTERM, shutting down");
        }
    
        return 1;
    }

    /* we've been told to restart */
    signal(SIGHUP, SIG_IGN);

    if (is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
		    AP_SIG_GRACEFUL_STRING " received.  Doing graceful restart");
    }
    else {
        /* Kill 'em all.  Since the child acts the same on the parents SIGTERM 
         * and a SIGHUP, we may as well use the same signal, because some user
         * pthreads are stealing signals from us left and right.
         */
	    
        ap_reclaim_child_processes(1);		/* Start with SIGTERM */
	    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
		    "SIGHUP received.  Attempting to restart");
    }
    
    /* just before we go, tidy up the locks we've created to prevent a 
     * potential leak of semaphores... */
    apr_thread_mutex_destroy(worker_thread_count_mutex);

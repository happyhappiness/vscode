
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
		"Server built: %s", ap_get_server_built());

    restart_pending = shutdown_pending = 0;

    /*
     * main_loop until it's all over
     */
    if (!one_process) {
        server_main_loop(remaining_threads_to_start);
    
        tell_workers_to_exit(); /* if we get here we're exiting... */
        sleep(1); /* give them a brief chance to exit */
    } else {
        proc_info *my_info = (proc_info *)malloc(sizeof(proc_info));
        my_info->slot = 0;
        apr_pool_create(&my_info->tpool, pchild);
        worker_thread(my_info);
    }
        
    /* close the UDP socket we've been using... */
    apr_socket_close(listening_sockets[0]);

    if ((one_process || shutdown_pending) && !child_fatal) {
        const char *pidfile = NULL;
        pidfile = ap_server_root_relative (pconf, ap_pid_fname);
        if ( pidfile != NULL && unlink(pidfile) == 0)
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
                         "removed PID file %s (pid=%ld)", pidfile, 
                         (long)getpid());
    }

    if (one_process) {
        return 1;
    }
        
    /*
     * If we get here we're shutting down...
     */
    if (shutdown_pending) {
        /* Time to gracefully shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        if (beosd_killpg(getpgrp(), SIGTERM) < 0)
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
             "killpg SIGTERM");
      
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
    apr_thread_mutex_destroy(accept_mutex);
    
    return 0;
}

static int beos_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
{
    static int restart_num = 0;

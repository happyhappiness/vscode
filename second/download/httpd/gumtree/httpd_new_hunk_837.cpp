
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
		"Server built: %s", ap_get_server_built());

    restart_pending = shutdown_pending = 0;

    mpm_state = AP_MPMQ_RUNNING;

    /* We sit in the server_main_loop() until we somehow manage to exit. When
     * we do, we need to kill the workers we have, so we start by using the
     * tell_workers_to_exit() function, but as it sometimes takes a short while
     * to accomplish this we have a pause builtin to allow them the chance to
     * gracefully exit.
     */
    if (!one_process) {
        server_main_loop(remaining_threads_to_start);
        tell_workers_to_exit();
        snooze(1000000);
    } else {
        worker_thread((void*)0);
    }
    mpm_state = AP_MPMQ_STOPPING;

    /* close the UDP socket we've been using... */
    apr_socket_close(udp_sock);

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
    } else {
        /* Kill 'em all.  Since the child acts the same on the parents SIGTERM
         * and a SIGHUP, we may as well use the same signal, because some user
         * pthreads are stealing signals from us left and right.
         */

        ap_reclaim_child_processes(1);   /* Start with SIGTERM */
	    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
		    "SIGHUP received.  Attempting to restart");
    }

    /* just before we go, tidy up the lock we created to prevent a
     * potential leak of semaphores...
     */
    apr_thread_mutex_destroy(accept_mutex);

    return 0;
}

static int beos_pre_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp)
{
    static int restart_num = 0;

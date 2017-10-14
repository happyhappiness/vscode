int ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
{
    int remaining_threads_to_start, i,j;
    apr_status_t rv;
    ap_listen_rec *lr;
    pconf = _pconf;
    ap_server_conf = s;

    /* Increase the available pool of fd's.  This code from
     * Joe Kloss <joek@be.com>
     */
    if( FD_SETSIZE > 128 && (i = _kset_fd_limit_( 128 )) < 0 ){
        ap_log_error(APLOG_MARK, APLOG_ERR, i, s,
            "could not set FD_SETSIZE (_kset_fd_limit_ failed)");
    }

    /* BeOS R5 doesn't support pipes on select() calls, so we use a
     * UDP socket as these are supported in both R5 and BONE.  If we only cared
     * about BONE we'd use a pipe, but there it is.
     * As we have UDP support in APR, now use the APR functions and check all the
     * return values...
     */
    if (apr_sockaddr_info_get(&udp_sa, "127.0.0.1", APR_UNSPEC, 7772, 0, _pconf)
        != APR_SUCCESS){
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, s,
            "couldn't create control socket information, shutting down");
        return 1;
    }
    if (apr_socket_create(&udp_sock, udp_sa->family, SOCK_DGRAM, 0,
                      _pconf) != APR_SUCCESS){
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, s,
            "couldn't create control socket, shutting down");
        return 1;
    }
    if (apr_socket_bind(udp_sock, udp_sa) != APR_SUCCESS){
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, s,
            "couldn't bind UDP socket!");
        return 1;
    }

    if ((num_listening_sockets = ap_setup_listeners(ap_server_conf)) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, s,
            "no listening sockets available, shutting down");
        return 1;
    }

    ap_log_pid(pconf, ap_pid_fname);

    /*
     * Create our locks...
     */

    /* accept_mutex
     * used to lock around select so we only have one thread
     * in select at a time
     */
    rv = apr_thread_mutex_create(&accept_mutex, 0, pconf);
    if (rv != APR_SUCCESS) {
        /* tsch tsch, can't have more than one thread in the accept loop
           at a time so we need to fall on our sword... */
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                     "Couldn't create accept lock");
        return 1;
    }

    /*
     * Startup/shutdown...
     */

    if (!is_graceful) {
        /* setup the scoreboard shared memory */
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            return 1;
        }

        for (i = 0; i < HARD_SERVER_LIMIT; i++) {
            ap_scoreboard_image->parent[i].pid = 0;
            for (j = 0;j < HARD_THREAD_LIMIT; j++)
                ap_scoreboard_image->servers[i][j].tid = 0;
        }
    }

    if (HARD_SERVER_LIMIT == 1)
        ap_scoreboard_image->parent[0].pid = getpid();

    set_signals();

    /* Sanity checks to avoid thrashing... */
    if (max_spare_threads < min_spare_threads )
        max_spare_threads = min_spare_threads;

    /* If we're doing a graceful_restart then we're going to see a lot
     * of threads exiting immediately when we get into the main loop
     * below (because we just sent them AP_SIG_GRACEFUL).  This happens
     * pretty rapidly... and for each one that exits we'll start a new one
     * until we reach at least threads_min_free.  But we may be permitted to
     * start more than that, so we'll just keep track of how many we're
     * supposed to start up without the 1 second penalty between each fork.
     */
    remaining_threads_to_start = ap_threads_to_start;
    /* sanity check on the number to start... */
    if (remaining_threads_to_start > ap_thread_limit) {
            remaining_threads_to_start = ap_thread_limit;
    }

    /* If we're doing the single process thing or we're in a graceful_restart
     * then we don't start threads here.
     * if we're in one_process mode we don't want to start threads
     * do we??
     */
    if (!is_graceful && !one_process) {
            startup_threads(remaining_threads_to_start);
            remaining_threads_to_start = 0;
    } else {
            /* give the system some time to recover before kicking into
             * exponential mode */
        hold_off_on_exponential_spawning = 10;
    }

    /*
     * record that we've entered the world !
     */
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                "%s configured -- resuming normal operations",
                ap_get_server_version());

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
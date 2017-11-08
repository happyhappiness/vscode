int ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
{
    int remaining_children_to_start;
    int i;
    apr_status_t rv;
    apr_size_t one = 1;
    ap_listen_rec *lr;
    apr_socket_t *sock = NULL;
    int fd;

    ap_log_pid(pconf, ap_pid_fname);

    first_server_limit = server_limit;
    first_thread_limit = thread_limit;
    if (changed_limit_at_restart) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "WARNING: Attempt to change ServerLimit or ThreadLimit "
                     "ignored during restart");
        changed_limit_at_restart = 0;
    }

    ap_server_conf = s;

    if ((ap_accept_lock_mech == APR_LOCK_SYSVSEM) || 
        (ap_accept_lock_mech == APR_LOCK_POSIXSEM)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "Server configured for an accept lock mechanism that "
                     "cannot be used with perchild.  Falling back to FCNTL.");
        ap_accept_lock_mech = APR_LOCK_FCNTL;
    }

    /* Initialize cross-process accept lock */
    ap_lock_fname = apr_psprintf(_pconf, "%s.%u",
                                 ap_server_root_relative(_pconf, ap_lock_fname),
                                 my_pid);
    rv = SAFE_ACCEPT(apr_proc_mutex_create(&process_accept_mutex,
                                     ap_lock_fname, ap_accept_lock_mech,
                                     _pconf));
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                     "Couldn't create cross-process lock");
        return 1;
    }

    if (!is_graceful) {
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            return 1;
        }
    }
    /* Initialize the child table */
    if (!is_graceful) {
        for (i = 0; i < server_limit; i++) {
            ap_child_table[i].pid = 0;
        }
    }

    /* We need to put the new listeners at the end of the ap_listeners
     * list.  If we don't, then the pool will be cleared before the
     * open_logs phase is called for the second time, and ap_listeners
     * will have only invalid data.  If that happens, then the sockets
     * that we opened using make_sock() will be lost, and the server
     * won't start.
     */
    for (lr = ap_listeners ; lr->next != NULL; lr = lr->next) {
        continue;
    }

    apr_os_file_get(&fd, pipe_of_death_in);
    apr_os_sock_put(&sock, &fd, pconf);
    lr->next = apr_palloc(pconf, sizeof(*lr));
    lr->next->sd = sock;
    lr->next->active = 1;
    lr->next->accept_func = check_pipe_of_death;
    lr->next->next = NULL;
    lr = lr->next;
    num_listensocks++;

    set_signals();

    /* If we're doing a graceful_restart then we're going to see a lot
     * of children exiting immediately when we get into the main loop
     * below (because we just sent them AP_SIG_GRACEFUL).  This happens 
     * pretty rapidly... and for each one that exits we'll start a new one 
     * until we reach at least daemons_min_free.  But we may be permitted to
     * start more than that, so we'll just keep track of how many we're
     * supposed to start up without the 1 second penalty between each fork.
     */
    remaining_children_to_start = num_daemons;
    if (!is_graceful) {
        remaining_children_to_start = \
            startup_children(remaining_children_to_start);
    }
    else {
        /* give the system some time to recover before kicking into
         * exponential mode */
        hold_off_on_exponential_spawning = 10;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                 "%s configured -- resuming normal operations",
                 ap_get_server_version());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
                 "Server built: %s", ap_get_server_built());
#ifdef AP_MPM_WANT_SET_ACCEPT_LOCK_MECH
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
		"AcceptMutex: %s (default: %s)",
		apr_proc_mutex_name(process_accept_mutex),
		apr_proc_mutex_defname());
#endif
    restart_pending = shutdown_pending = 0;

    server_main_loop(remaining_children_to_start);

    if (shutdown_pending) {
        /* Time to gracefully shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        if (unixd_killpg(getpgrp(), SIGTERM) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                         "killpg SIGTERM");
        }
        ap_reclaim_child_processes(1);      /* Start with SIGTERM */

        if (!child_fatal) {
            /* cleanup pid file on normal shutdown */
            const char *pidfile = NULL;
            pidfile = ap_server_root_relative (pconf, ap_pid_fname);
            if (pidfile != NULL && unlink(pidfile) == 0) {
                ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             ap_server_conf,
                             "removed PID file %s (pid=%ld)",
                             pidfile, (long)getpid());
            }
    
            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0,
                         ap_server_conf, "caught SIGTERM, shutting down");
        }
        return 1;
    }

    /* we've been told to restart */
    apr_signal(SIGHUP, SIG_IGN);

    if (one_process) {
        /* not worth thinking about */
        return 1;
    }

    if (is_graceful) {
        char char_of_death = '!';

        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0,
                     ap_server_conf, AP_SIG_GRACEFUL_STRING " received.  "
                     "Doing graceful restart");

        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.
         */
    
        for (i = 0; i < num_daemons; ++i) {
            if (ap_child_table[i].pid) {
                ap_child_table[i].status = SERVER_DYING;
            } 
        }
        /* give the children the signal to die */
        for (i = 0; i < num_daemons;) {
            if ((rv = apr_file_write(pipe_of_death_out, &char_of_death,
                                     &one)) != APR_SUCCESS) {
                if (APR_STATUS_IS_EINTR(rv)) continue;
                ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                             "write pipe_of_death");
            }
            i++;
        }
    }
    else {
        /* Kill 'em all.  Since the child acts the same on the parents SIGTERM 
         * and a SIGHUP, we may as well use the same signal, because some user
         * pthreads are stealing signals from us left and right.
         */
        if (unixd_killpg(getpgrp(), SIGTERM) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                         "killpg SIGTERM");
        }
        ap_reclaim_child_processes(1);      /* Start with SIGTERM */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0,
                     ap_server_conf, "SIGHUP received.  Attempting to restart");
    }
    return 0;
}
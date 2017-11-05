static void child_main(int child_num_arg)
{
#if APR_HAS_THREADS
    apr_thread_t *thd = NULL;
    apr_os_thread_t osthd;
#endif
    apr_pool_t *ptrans;
    apr_allocator_t *allocator;
    apr_status_t status;
    int i;
    ap_listen_rec *lr;
    apr_pollset_t *pollset;
    ap_sb_handle_t *sbh;
    apr_bucket_alloc_t *bucket_alloc;
    int last_poll_idx = 0;
    const char *lockfile;

    mpm_state = AP_MPMQ_STARTING; /* for benefit of any hooks that run as this
                                   * child initializes
                                   */

    my_child_num = child_num_arg;
    ap_my_pid = getpid();
    requests_this_child = 0;

    ap_fatal_signal_child_setup(ap_server_conf);

    /* Get a sub context for global allocations in this child, so that
     * we can have cleanups occur when the child exits.
     */
    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    apr_pool_create_ex(&pchild, pconf, NULL, allocator);
    apr_allocator_owner_set(allocator, pchild);
    apr_pool_tag(pchild, "pchild");

#if APR_HAS_THREADS
    osthd = apr_os_thread_current();
    apr_os_thread_put(&thd, &osthd, pchild);
#endif
    
    apr_pool_create(&ptrans, pchild);
    apr_pool_tag(ptrans, "transaction");

    /* needs to be done before we switch UIDs so we have permissions */
    ap_reopen_scoreboard(pchild, NULL, 0);
    lockfile = apr_proc_mutex_lockfile(accept_mutex);
    status = apr_proc_mutex_child_init(&accept_mutex,
                                       lockfile,
                                       pchild);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                     "Couldn't initialize cross-process lock in child "
                     "(%s) (%s)",
                     lockfile ? lockfile : "none",
                     apr_proc_mutex_name(accept_mutex));
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    if (ap_run_drop_privileges(pchild, ap_server_conf)) {
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    ap_run_child_init(pchild, ap_server_conf);

    ap_create_sb_handle(&sbh, pchild, my_child_num, 0);

    (void) ap_update_child_status(sbh, SERVER_READY, (request_rec *) NULL);

    /* Set up the pollfd array */
    status = apr_pollset_create(&pollset, num_listensocks, pchild, 0);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                     "Couldn't create pollset in child; check system or user limits");
        clean_child_exit(APEXIT_CHILDSICK); /* assume temporary resource issue */
    }

    for (lr = ap_listeners, i = num_listensocks; i--; lr = lr->next) {
        apr_pollfd_t pfd = { 0 };

        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = lr->sd;
        pfd.reqevents = APR_POLLIN;
        pfd.client_data = lr;

        status = apr_pollset_add(pollset, &pfd);
        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                         "Couldn't add listener to pollset; check system or user limits");
            clean_child_exit(APEXIT_CHILDSICK);
        }

        lr->accept_func = ap_unixd_accept;
    }

    mpm_state = AP_MPMQ_RUNNING;

    bucket_alloc = apr_bucket_alloc_create(pchild);

    /* die_now is set when AP_SIG_GRACEFUL is received in the child;
     * shutdown_pending is set when SIGTERM is received when running
     * in single process mode.  */
    while (!die_now && !shutdown_pending) {
        conn_rec *current_conn;
        void *csd;

        /*
         * (Re)initialize this child to a pre-connection state.
         */

        apr_pool_clear(ptrans);

        if ((ap_max_requests_per_child > 0
             && requests_this_child++ >= ap_max_requests_per_child)) {
            clean_child_exit(0);
        }

        (void) ap_update_child_status(sbh, SERVER_READY, (request_rec *) NULL);

        /*
         * Wait for an acceptable connection to arrive.
         */

        /* Lock around "accept", if necessary */
        SAFE_ACCEPT(accept_mutex_on());

        if (num_listensocks == 1) {
            /* There is only one listener record, so refer to that one. */
            lr = ap_listeners;
        }
        else {
            /* multiple listening sockets - need to poll */
            for (;;) {
                apr_int32_t numdesc;
                const apr_pollfd_t *pdesc;

                /* check for termination first so we don't sleep for a while in
                 * poll if already signalled
                 */
                if (one_process && shutdown_pending) {
                    SAFE_ACCEPT(accept_mutex_off());
                    return;
                }
                else if (die_now) {
                    /* In graceful stop/restart; drop the mutex
                     * and terminate the child. */
                    SAFE_ACCEPT(accept_mutex_off());
                    clean_child_exit(0);
                }
                /* timeout == 10 seconds to avoid a hang at graceful restart/stop
                 * caused by the closing of sockets by the signal handler
                 */
                status = apr_pollset_poll(pollset, apr_time_from_sec(10), 
                                          &numdesc, &pdesc);
                if (status != APR_SUCCESS) {
                    if (APR_STATUS_IS_TIMEUP(status) ||
                        APR_STATUS_IS_EINTR(status)) {
                        continue;
                    }
                    /* Single Unix documents select as returning errnos
                     * EBADF, EINTR, and EINVAL... and in none of those
                     * cases does it make sense to continue.  In fact
                     * on Linux 2.0.x we seem to end up with EFAULT
                     * occasionally, and we'd loop forever due to it.
                     */
                    ap_log_error(APLOG_MARK, APLOG_ERR, status,
                                 ap_server_conf, "apr_pollset_poll: (listen)");
                    SAFE_ACCEPT(accept_mutex_off());
                    clean_child_exit(1);
                }

                /* We can always use pdesc[0], but sockets at position N
                 * could end up completely starved of attention in a very
                 * busy server. Therefore, we round-robin across the
                 * returned set of descriptors. While it is possible that
                 * the returned set of descriptors might flip around and
                 * continue to starve some sockets, we happen to know the
                 * internal pollset implementation retains ordering
                 * stability of the sockets. Thus, the round-robin should
                 * ensure that a socket will eventually be serviced.
                 */
                if (last_poll_idx >= numdesc)
                    last_poll_idx = 0;

                /* Grab a listener record from the client_data of the poll
                 * descriptor, and advance our saved index to round-robin
                 * the next fetch.
                 *
                 * ### hmm... this descriptor might have POLLERR rather
                 * ### than POLLIN
                 */
                lr = pdesc[last_poll_idx++].client_data;
                goto got_fd;
            }
        }
    got_fd:
        /* if we accept() something we don't want to die, so we have to
         * defer the exit
         */
        status = lr->accept_func(&csd, lr, ptrans);

        SAFE_ACCEPT(accept_mutex_off());      /* unlock after "accept" */

        if (status == APR_EGENERAL) {
            /* resource shortage or should-not-occur occured */
            clean_child_exit(1);
        }
        else if (status != APR_SUCCESS) {
            continue;
        }

        /*
         * We now have a connection, so set it up with the appropriate
         * socket options, file descriptors, and read/write buffers.
         */

        current_conn = ap_run_create_connection(ptrans, ap_server_conf, csd, my_child_num, sbh, bucket_alloc);
        if (current_conn) {
#if APR_HAS_THREADS
            current_conn->current_thread = thd;
#endif
            ap_process_connection(current_conn, csd);
            ap_lingering_close(current_conn);
        }

        /* Check the pod and the generation number after processing a
         * connection so that we'll go away if a graceful restart occurred
         * while we were processing the connection or we are the lucky
         * idle server process that gets to die.
         */
        if (ap_mpm_pod_check(pod) == APR_SUCCESS) { /* selected as idle? */
            die_now = 1;
        }
        else if (my_generation !=
                 ap_scoreboard_image->global->running_generation) { /* restart? */
            /* yeah, this could be non-graceful restart, in which case the
             * parent will kill us soon enough, but why bother checking?
             */
            die_now = 1;
        }
    }
    apr_pool_clear(ptrans);
    clean_child_exit(0);
}
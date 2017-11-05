static void child_main(int child_num_arg)
{
    apr_pool_t *ptrans;
    apr_allocator_t *allocator;
    conn_rec *current_conn;
    apr_status_t status = APR_EINIT;
    int i;
    ap_listen_rec *lr;
    int curr_pollfd, last_pollfd = 0;
    apr_pollfd_t *pollset;
    int offset;
    void *csd;
    ap_sb_handle_t *sbh;
    apr_status_t rv;
    apr_bucket_alloc_t *bucket_alloc;

    mpm_state = AP_MPMQ_STARTING; /* for benefit of any hooks that run as this
                                  * child initializes
                                  */
    
    my_child_num = child_num_arg;
    ap_my_pid = getpid();
    csd = NULL;
    requests_this_child = 0;

    ap_fatal_signal_child_setup(ap_server_conf);

    /* Get a sub context for global allocations in this child, so that
     * we can have cleanups occur when the child exits.
     */
    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    apr_pool_create_ex(&pchild, pconf, NULL, allocator);
    apr_allocator_owner_set(allocator, pchild);

    apr_pool_create(&ptrans, pchild);
    apr_pool_tag(ptrans, "transaction");

    /* needs to be done before we switch UIDs so we have permissions */
    ap_reopen_scoreboard(pchild, NULL, 0);
    rv = apr_proc_mutex_child_init(&accept_mutex, ap_lock_fname, pchild);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "Couldn't initialize cross-process lock in child");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    if (unixd_setup_child()) {
	clean_child_exit(APEXIT_CHILDFATAL);
    }

    ap_run_child_init(pchild, ap_server_conf);

    ap_create_sb_handle(&sbh, pchild, my_child_num, 0);

    (void) ap_update_child_status(sbh, SERVER_READY, (request_rec *) NULL);

    /* Set up the pollfd array */
    listensocks = apr_pcalloc(pchild,
                            sizeof(*listensocks) * (num_listensocks));
    for (lr = ap_listeners, i = 0; i < num_listensocks; lr = lr->next, i++) {
        listensocks[i].accept_func = lr->accept_func;
        listensocks[i].sd = lr->sd;
    }

    pollset = apr_palloc(pchild, sizeof(*pollset) * num_listensocks);
    pollset[0].p = pchild;
    for (i = 0; i < num_listensocks; i++) {
        pollset[i].desc.s = listensocks[i].sd;
        pollset[i].desc_type = APR_POLL_SOCKET;
        pollset[i].reqevents = APR_POLLIN;
    }

    mpm_state = AP_MPMQ_RUNNING;
    
    bucket_alloc = apr_bucket_alloc_create(pchild);

    while (!die_now) {
	/*
	 * (Re)initialize this child to a pre-connection state.
	 */

	current_conn = NULL;

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
            offset = 0;
        }
        else {
            /* multiple listening sockets - need to poll */
	    for (;;) {
                apr_status_t ret;
                apr_int32_t n;

                ret = apr_poll(pollset, num_listensocks, &n, -1);
                if (ret != APR_SUCCESS) {
                    if (APR_STATUS_IS_EINTR(ret)) {
                        continue;
                    }
    	            /* Single Unix documents select as returning errnos
    	             * EBADF, EINTR, and EINVAL... and in none of those
    	             * cases does it make sense to continue.  In fact
    	             * on Linux 2.0.x we seem to end up with EFAULT
    	             * occasionally, and we'd loop forever due to it.
    	             */
    	            ap_log_error(APLOG_MARK, APLOG_ERR, ret, ap_server_conf,
                             "apr_poll: (listen)");
    	            clean_child_exit(1);
                }
                /* find a listener */
                curr_pollfd = last_pollfd;
                do {
                    curr_pollfd++;
                    if (curr_pollfd >= num_listensocks) {
                        curr_pollfd = 0;
                    }
                    /* XXX: Should we check for POLLERR? */
                    if (pollset[curr_pollfd].rtnevents & APR_POLLIN) {
                        last_pollfd = curr_pollfd;
                        offset = curr_pollfd;
                        goto got_fd;
                    }
                } while (curr_pollfd != last_pollfd);

                continue;
            }
        }
    got_fd:
	/* if we accept() something we don't want to die, so we have to
	 * defer the exit
	 */
        status = listensocks[offset].accept_func(&csd, 
                                                 &listensocks[offset], ptrans);
        SAFE_ACCEPT(accept_mutex_off());	/* unlock after "accept" */

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
        else if (ap_my_generation !=
                 ap_scoreboard_image->global->running_generation) { /* restart? */
            /* yeah, this could be non-graceful restart, in which case the
             * parent will kill us soon enough, but why bother checking?
             */
            die_now = 1;
        }
    }
    clean_child_exit(0);
}
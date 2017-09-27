/*****************************************************************
 * Here follows a long bunch of generic server bookkeeping stuff...
 */

int ap_graceful_stop_signalled(void)
{
    return is_graceful;
}

/* This is the thread that actually does all the work. */
static int32 worker_thread(void *dummy)
{
    int worker_slot = (int)dummy;
    apr_allocator_t *allocator;
    apr_bucket_alloc_t *bucket_alloc;
    apr_status_t rv = APR_EINIT;
    int last_poll_idx = 0;
    sigset_t sig_mask;
    int requests_this_child = 0;
    apr_pollset_t *pollset = NULL;
    ap_listen_rec *lr = NULL;
    ap_sb_handle_t *sbh = NULL;
    int i;
    /* each worker thread is in control of its own destiny...*/
    int this_worker_should_exit = 0;
    /* We have 2 pools that we create/use throughout the lifetime of this
     * worker. The first and longest lived is the pworker pool. From
     * this we create the ptrans pool, the lifetime of which is the same
     * as each connection and is reset prior to each attempt to
     * process a connection.
     */
    apr_pool_t *ptrans = NULL;
    apr_pool_t *pworker = NULL;

    mpm_state = AP_MPMQ_STARTING; /* for benefit of any hooks that run as this
                                  * child initializes
                                  */

    on_exit_thread(check_restart, (void*)worker_slot);

    /* block the signals for this thread only if we're not running as a
     * single process.
     */
    if (!one_process) {
        sigfillset(&sig_mask);
        sigprocmask(SIG_BLOCK, &sig_mask, NULL);
    }

    /* Each worker thread is fully in control of it's destinay and so
     * to allow each thread to handle the lifetime of it's own resources
     * we create and use a subcontext for every thread.
     * The subcontext is a child of the pconf pool.
     */
    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    apr_pool_create_ex(&pworker, pconf, NULL, allocator);
    apr_allocator_owner_set(allocator, pworker);

    apr_pool_create(&ptrans, pworker);
    apr_pool_tag(ptrans, "transaction");

    ap_create_sb_handle(&sbh, pworker, 0, worker_slot);
    (void) ap_update_child_status(sbh, SERVER_READY, (request_rec *) NULL);

    /* We add an extra socket here as we add the udp_sock we use for signalling
     * death. This gets added after the others.
     */
    apr_pollset_create(&pollset, num_listening_sockets + 1, pworker, 0);

    for (lr = ap_listeners, i = num_listening_sockets; i--; lr = lr->next) {
        apr_pollfd_t pfd = {0};

        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = lr->sd;
        pfd.reqevents = APR_POLLIN;
        pfd.client_data = lr;

        apr_pollset_add(pollset, &pfd);
    }
    {
        apr_pollfd_t pfd = {0};

        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = udp_sock;
        pfd.reqevents = APR_POLLIN;

        apr_pollset_add(pollset, &pfd);
    }

    bucket_alloc = apr_bucket_alloc_create(pworker);

    mpm_state = AP_MPMQ_RUNNING;

        while (!this_worker_should_exit) {
        conn_rec *current_conn;
        void *csd;

        /* (Re)initialize this child to a pre-connection state. */
        apr_pool_clear(ptrans);

        if ((ap_max_requests_per_thread > 0
             && requests_this_child++ >= ap_max_requests_per_thread))
            clean_child_exit(0, worker_slot);

        (void) ap_update_child_status(sbh, SERVER_READY, (request_rec *) NULL);

        apr_thread_mutex_lock(accept_mutex);

        /* We always (presently) have at least 2 sockets we listen on, so
         * we don't have the ability for a fast path for a single socket
         * as some MPM's allow :(
         */
        for (;;) {
            apr_int32_t numdesc = 0;
            const apr_pollfd_t *pdesc = NULL;

            rv = apr_pollset_poll(pollset, -1, &numdesc, &pdesc);
            if (rv != APR_SUCCESS) {
                if (APR_STATUS_IS_EINTR(rv)) {
                    if (one_process && shutdown_pending)
                        return;
                    continue;
                }
                ap_log_error(APLOG_MARK, APLOG_ERR, rv,
                             ap_server_conf, "apr_pollset_poll: (listen)");
                clean_child_exit(1, worker_slot);
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

            /* The only socket we add without client_data is the first, the UDP socket
             * we listen on for restart signals. If we've therefore gotten a hit on that
             * listener lr will be NULL here and we know we've been told to die.
             * Before we jump to the end of the while loop with this_worker_should_exit
             * set to 1 (causing us to exit normally we hope) we release the accept_mutex
             * as we want every thread to go through this same routine :)
             * Bit of a hack, but compared to what I had before...
             */
            if (lr == NULL) {
                this_worker_should_exit = 1;
                apr_thread_mutex_unlock(accept_mutex);
                goto got_a_black_spot;
            }
            goto got_fd;
        }
got_fd:
        /* Run beos_accept to accept the connection and set things up to
         * allow us to process it. We always release the accept_lock here,
         * even if we failt o accept as otherwise we'll starve other workers
         * which would be bad.
         */
        rv = beos_accept(&csd, lr, ptrans);
        apr_thread_mutex_unlock(accept_mutex);

        if (rv == APR_EGENERAL) {
            /* resource shortage or should-not-occur occured */
            clean_child_exit(1, worker_slot);
        } else if (rv != APR_SUCCESS)
            continue;

        current_conn = ap_run_create_connection(ptrans, ap_server_conf, csd, worker_slot, sbh, bucket_alloc);
        if (current_conn) {
            ap_process_connection(current_conn, csd);
            ap_lingering_close(current_conn);
        }

        if (ap_my_generation !=
                 ap_scoreboard_image->global->running_generation) { /* restart? */
            /* yeah, this could be non-graceful restart, in which case the
             * parent will kill us soon enough, but why bother checking?
             */
            this_worker_should_exit = 1;
        }
got_a_black_spot:
    }

    apr_pool_destroy(ptrans);
    apr_pool_destroy(pworker);

    clean_child_exit(0, worker_slot);
}

static int make_worker(int slot)
{
    thread_id tid;

    if (slot + 1 > ap_max_child_assigned)
	    ap_max_child_assigned = slot + 1;

    (void) ap_update_child_status_from_indexes(0, slot, SERVER_STARTING, (request_rec*)NULL);

    if (one_process) {
    	set_signals();
        ap_scoreboard_image->parent[0].pid = getpid();
        ap_scoreboard_image->servers[0][slot].tid = find_thread(NULL);
        return 0;
    }

    tid = spawn_thread(worker_thread, "apache_worker", B_NORMAL_PRIORITY,
                       (void *)slot);
    if (tid < B_NO_ERROR) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, NULL,
            "spawn_thread: Unable to start a new thread");
        /* In case system resources are maxed out, we don't want
         * Apache running away with the CPU trying to fork over and
         * over and over again.
         */
        (void) ap_update_child_status_from_indexes(0, slot, SERVER_DEAD,
                                                   (request_rec*)NULL);

    	sleep(10);
    	return -1;
    }
    resume_thread(tid);

    ap_scoreboard_image->servers[0][slot].tid = tid;
    return 0;
}

/* When a worker thread exits, this function is called. If we are not in
 * a shutdown situation then we restart the worker in the slot that was
 * just vacated.
 */
static void check_restart(void *data)
{
    if (!restart_pending && !shutdown_pending) {
        int slot = (int)data;
        make_worker(slot);
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL,
                     "spawning a new worker thread in slot %d", slot);
    }
}

/* Start number_to_start children. This is used to start both the
 * initial 'pool' of workers but also to replace existing workers who
 * have reached the end of their time. It walks through the scoreboard to find
 * an empty slot and starts the worker thread in that slot.
 */
static void startup_threads(int number_to_start)
{
    int i;

    for (i = 0; number_to_start && i < ap_thread_limit; ++i) {
        if (ap_scoreboard_image->servers[0][i].tid)
	    continue;

        if (make_worker(i) < 0)
                break;

	--number_to_start;
    }
}


/*

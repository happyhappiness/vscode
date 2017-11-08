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
       
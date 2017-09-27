    ap_listen_rec *lr;
    int have_idle_worker = 0;
    int last_poll_idx = 0;

    free(ti);

    /* ### check the status */
    (void) apr_pollset_create(&pollset, num_listensocks, tpool, 0);

    for (lr = ap_listeners; lr != NULL; lr = lr->next) {
        apr_pollfd_t pfd = { 0 };

        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = lr->sd;
        pfd.reqevents = APR_POLLIN;
        pfd.client_data = lr;

        /* ### check the status */
        (void) apr_pollset_add(pollset, &pfd);
    }

    /* Unblock the signal used to wake this thread up, and set a handler for
     * it.
     */
    unblock_signal(LISTENER_SIGNAL);

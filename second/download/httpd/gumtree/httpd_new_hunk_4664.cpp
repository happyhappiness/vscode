
    ap_create_sb_handle(&sbh, pchild, my_child_num, 0);

    (void) ap_update_child_status(sbh, SERVER_READY, (request_rec *) NULL);

    /* Set up the pollfd array */
    status = apr_pollset_create(&pollset, num_listensocks, pchild,
                                APR_POLLSET_NOCOPY);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf, APLOGNO(00156)
                     "Couldn't create pollset in child; check system or user limits");
        clean_child_exit(APEXIT_CHILDSICK); /* assume temporary resource issue */
    }

    for (lr = my_bucket->listeners, i = num_listensocks; i--; lr = lr->next) {
        apr_pollfd_t *pfd = apr_pcalloc(pchild, sizeof *pfd);

        pfd->desc_type = APR_POLL_SOCKET;
        pfd->desc.s = lr->sd;
        pfd->reqevents = APR_POLLIN;
        pfd->client_data = lr;

        status = apr_pollset_add(pollset, pfd);
        if (status != APR_SUCCESS) {
            /* If the child processed a SIGWINCH before setting up the
             * pollset, this error path is expected and harmless,
             * since the listener fd was already closed; so don't
             * pollute the logs in that case. */
            if (!die_now) {

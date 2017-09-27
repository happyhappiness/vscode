    ap_listen_rec *lr;
    int have_idle_worker = 0;
    int last_poll_idx = 0;

    free(ti);

    rv = apr_pollset_create(&pollset, num_listensocks, tpool,
                            APR_POLLSET_NOCOPY);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "Couldn't create pollset in thread;"
                     " check system or user limits");
        /* let the parent decide how bad this really is */
        clean_child_exit(APEXIT_CHILDSICK);
    }

    for (lr = my_bucket->listeners; lr != NULL; lr = lr->next) {
        apr_pollfd_t *pfd = apr_pcalloc(tpool, sizeof *pfd);

        pfd->desc_type = APR_POLL_SOCKET;
        pfd->desc.s = lr->sd;
        pfd->reqevents = APR_POLLIN;
        pfd->client_data = lr;

        rv = apr_pollset_add(pollset, pfd);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                         "Couldn't create add listener to pollset;"
                         " check system or user limits");
            /* let the parent decide how bad this really is */
            clean_child_exit(APEXIT_CHILDSICK);

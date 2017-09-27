    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf, APLOGNO(00156)
                     "Couldn't create pollset in child; check system or user limits");
        clean_child_exit(APEXIT_CHILDSICK); /* assume temporary resource issue */
    }

    for (lr = my_bucket->listeners, i = num_listensocks; i--; lr = lr->next) {
        apr_pollfd_t pfd = { 0 };

        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = lr->sd;
        pfd.reqevents = APR_POLLIN;
        pfd.client_data = lr;

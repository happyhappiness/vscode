
        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = lr->sd;
        pfd.reqevents = APR_POLLIN;
        pfd.client_data = lr;

        /* ### check the status */
        (void) apr_pollset_add(pollset, &pfd);
    }

    mpm_state = AP_MPMQ_RUNNING;

    bucket_alloc = apr_bucket_alloc_create(pchild);


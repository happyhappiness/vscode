
    /* Set up poll */
    for (num_listeners = 0, lr = ap_listeners; lr; lr = lr->next) {
        num_listeners++;
    }

    apr_poll_setup(&pollset, num_listeners, pchild);

    for (lr = ap_listeners; lr; lr = lr->next) {
        apr_poll_socket_add(pollset, lr->sd, APR_POLLIN);
    }

    /* Main connection accept loop */
    do {
        apr_pool_t *pconn;
        worker_args_t *worker_args;

        apr_pool_create(&pconn, pchild);
        worker_args = apr_palloc(pconn, sizeof(worker_args_t));
        worker_args->pconn = pconn;

        if (num_listeners == 1) {
            rv = apr_accept(&worker_args->conn_sd, ap_listeners->sd, pconn);
        } else {
            rc = DosRequestMutexSem(ap_mpm_accept_mutex, SEM_INDEFINITE_WAIT);

            if (shutdown_pending) {
                DosReleaseMutexSem(ap_mpm_accept_mutex);
                break;
            }

            rv = APR_FROM_OS_ERROR(rc);

            if (rv == APR_SUCCESS) {
                rv = apr_poll(pollset, num_listeners, &nsds, -1);
                DosReleaseMutexSem(ap_mpm_accept_mutex);
            }

            if (rv == APR_SUCCESS) {
                if (first_lr == NULL) {
                    first_lr = ap_listeners;
                }

                lr = first_lr;

                do {
                    apr_int16_t event;

                    apr_poll_revents_get(&event, lr->sd, pollset);

                    if (event == APR_POLLIN) {
                        apr_sockaddr_t *sa;
                        apr_port_t port;
                        apr_socket_addr_get(&sa, APR_LOCAL, lr->sd);
                        apr_sockaddr_port_get(&port, sa);
                        first_lr = lr->next;
                        break;
                    }
                    lr = lr->next;

                    if (!lr) {
                        lr = ap_listeners;
                    }
                } while (lr != first_lr);

                if (lr == first_lr) {
                    continue;
                }

                sd = lr->sd;
                rv = apr_accept(&worker_args->conn_sd, sd, pconn);
            }
        }

        if (rv != APR_SUCCESS) {
            if (!APR_STATUS_IS_EINTR(rv)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                             "apr_accept");
                clean_child_exit(APEXIT_CHILDFATAL);
            }
        } else {
            DosWriteQueue(workq, WORKTYPE_CONN, sizeof(worker_args_t), worker_args, 0);
            requests_this_child++;
        }

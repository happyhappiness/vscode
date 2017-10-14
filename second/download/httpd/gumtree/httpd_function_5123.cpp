void ap_mpm_child_main(apr_pool_t *pconf)
{
    ap_listen_rec *lr = NULL;
    int requests_this_child = 0;
    int rv = 0;
    unsigned long ulTimes;
    int my_pid = getpid();
    ULONG rc, c;
    HQUEUE workq;
    apr_pollset_t *pollset;
    int num_listeners;
    TID server_maint_tid;
    void *sb_mem;

    /* Stop Ctrl-C/Ctrl-Break signals going to child processes */
    DosSetSignalExceptionFocus(0, &ulTimes);
    set_signals();

    /* Create pool for child */
    apr_pool_create(&pchild, pconf);

    ap_run_child_init(pchild, ap_server_conf);

    /* Create an event semaphore used to trigger other threads to shutdown */
    rc = DosCreateEventSem(NULL, &shutdown_event, 0, FALSE);

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "unable to create shutdown semaphore, exiting");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* Gain access to the scoreboard. */
    rc = DosGetNamedSharedMem(&sb_mem, ap_scoreboard_fname,
                              PAG_READ|PAG_WRITE);

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "scoreboard not readable in child, exiting");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    ap_calc_scoreboard_size();
    ap_init_scoreboard(sb_mem);

    /* Gain access to the accpet mutex */
    rc = DosOpenMutexSem(NULL, &ap_mpm_accept_mutex);

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "accept mutex couldn't be accessed in child, exiting");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* Find our pid in the scoreboard so we know what slot our parent allocated us */
    for (child_slot = 0; ap_scoreboard_image->parent[child_slot].pid != my_pid && child_slot < HARD_SERVER_LIMIT; child_slot++);

    if (child_slot == HARD_SERVER_LIMIT) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
                     "child pid not found in scoreboard, exiting");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    ap_my_generation = ap_scoreboard_image->parent[child_slot].generation;
    memset(ap_scoreboard_image->servers[child_slot], 0, sizeof(worker_score) * HARD_THREAD_LIMIT);

    /* Set up an OS/2 queue for passing connections & termination requests
     * to worker threads
     */
    rc = DosCreateQueue(&workq, QUE_FIFO, apr_psprintf(pchild, "/queues/httpd/work.%d", my_pid));

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "unable to create work queue, exiting");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* Create initial pool of worker threads */
    for (c = 0; c < ap_min_spare_threads; c++) {
//        ap_scoreboard_image->servers[child_slot][c].tid = _beginthread(worker_main, NULL, 128*1024, (void *)c);
    }

    /* Start maintenance thread */
    server_maint_tid = _beginthread(server_maintenance, NULL, 32768, NULL);

    /* Set up poll */
    for (num_listeners = 0, lr = ap_listeners; lr; lr = lr->next) {
        num_listeners++;
    }

    apr_pollset_create(&pollset, num_listeners, pchild, 0);

    for (lr = ap_listeners; lr != NULL; lr = lr->next) {
        apr_pollfd_t pfd = { 0 };

        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = lr->sd;
        pfd.reqevents = APR_POLLIN;
        pfd.client_data = lr;
        apr_pollset_add(pollset, &pfd);
    }

    /* Main connection accept loop */
    do {
        apr_pool_t *pconn;
        worker_args_t *worker_args;
        int last_poll_idx = 0;

        apr_pool_create(&pconn, pchild);
        worker_args = apr_palloc(pconn, sizeof(worker_args_t));
        worker_args->pconn = pconn;

        if (num_listeners == 1) {
            rv = apr_socket_accept(&worker_args->conn_sd, ap_listeners->sd, pconn);
        } else {
            const apr_pollfd_t *poll_results;
            apr_int32_t num_poll_results;

            rc = DosRequestMutexSem(ap_mpm_accept_mutex, SEM_INDEFINITE_WAIT);

            if (shutdown_pending) {
                DosReleaseMutexSem(ap_mpm_accept_mutex);
                break;
            }

            rv = APR_FROM_OS_ERROR(rc);

            if (rv == APR_SUCCESS) {
                rv = apr_pollset_poll(pollset, -1, &num_poll_results, &poll_results);
                DosReleaseMutexSem(ap_mpm_accept_mutex);
            }

            if (rv == APR_SUCCESS) {
                if (last_poll_idx >= num_listeners) {
                    last_poll_idx = 0;
                }

                lr = poll_results[last_poll_idx++].client_data;
                rv = apr_socket_accept(&worker_args->conn_sd, lr->sd, pconn);
                last_poll_idx++;
            }
        }

        if (rv != APR_SUCCESS) {
            if (!APR_STATUS_IS_EINTR(rv)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                             "apr_socket_accept");
                clean_child_exit(APEXIT_CHILDFATAL);
            }
        } else {
            DosWriteQueue(workq, WORKTYPE_CONN, sizeof(worker_args_t), worker_args, 0);
            requests_this_child++;
        }

        if (ap_max_requests_per_child != 0 && requests_this_child >= ap_max_requests_per_child)
            break;
    } while (!shutdown_pending && ap_my_generation == ap_scoreboard_image->global->running_generation);

    ap_scoreboard_image->parent[child_slot].quiescing = 1;
    DosPostEventSem(shutdown_event);
    DosWaitThread(&server_maint_tid, DCWW_WAIT);

    if (is_graceful) {
        char someleft;

        /* tell our worker threads to exit */
        for (c=0; c<HARD_THREAD_LIMIT; c++) {
            if (ap_scoreboard_image->servers[child_slot][c].status != SERVER_DEAD) {
                DosWriteQueue(workq, WORKTYPE_EXIT, 0, NULL, 0);
            }
        }

        do {
            someleft = 0;

            for (c=0; c<HARD_THREAD_LIMIT; c++) {
                if (ap_scoreboard_image->servers[child_slot][c].status != SERVER_DEAD) {
                    someleft = 1;
                    DosSleep(1000);
                    break;
                }
            }
        } while (someleft);
    } else {
        DosPurgeQueue(workq);

        for (c=0; c<HARD_THREAD_LIMIT; c++) {
            if (ap_scoreboard_image->servers[child_slot][c].status != SERVER_DEAD) {
                DosKillThread(ap_scoreboard_image->servers[child_slot][c].tid);
            }
        }
    }

    apr_pool_destroy(pchild);
}
void worker_main(void *arg)
{
    ap_listen_rec *lr, *first_lr, *last_lr = NULL;
    apr_pool_t *ptrans;
    apr_allocator_t *allocator;
    apr_bucket_alloc_t *bucket_alloc;
    conn_rec *current_conn;
    apr_status_t stat = APR_EINIT;
    ap_sb_handle_t *sbh;

    int my_worker_num = (int)arg;
    apr_socket_t *csd = NULL;
    int requests_this_child = 0;
    apr_socket_t *sd = NULL;
    fd_set main_fds;

    int sockdes;
    int srv;
    struct timeval tv;
    int wouldblock_retry;

    tv.tv_sec = 1;
    tv.tv_usec = 0;

    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);

    apr_pool_create_ex(&ptrans, pmain, NULL, allocator);
    apr_allocator_owner_set(allocator, ptrans);
    apr_pool_tag(ptrans, "transaction");

    bucket_alloc = apr_bucket_alloc_create_ex(allocator);

    atomic_inc (&worker_thread_count);

    while (!die_now) {
        /*
        * (Re)initialize this child to a pre-connection state.
        */
        current_conn = NULL;
        apr_pool_clear(ptrans);

        if ((ap_max_requests_per_child > 0
            && requests_this_child++ >= ap_max_requests_per_child)) {
            DBPRINT1 ("\n**Thread slot %d is shutting down", my_worker_num);
            clean_child_exit(0, my_worker_num, ptrans, bucket_alloc);
        }

        ap_update_child_status_from_indexes(0, my_worker_num, WORKER_READY,
                                            (request_rec *) NULL);

        /*
        * Wait for an acceptable connection to arrive.
        */

        for (;;) {
            if (shutdown_pending || restart_pending || (ap_scoreboard_image->servers[0][my_worker_num].status == WORKER_IDLE_KILL)) {
                DBPRINT1 ("\nThread slot %d is shutting down\n", my_worker_num);
                clean_child_exit(0, my_worker_num, ptrans, bucket_alloc);
            }

            /* Check the listen queue on all sockets for requests */
            memcpy(&main_fds, &listenfds, sizeof(fd_set));
            srv = select(listenmaxfd + 1, &main_fds, NULL, NULL, &tv);

            if (srv <= 0) {
                if (srv < 0) {
                    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                        "select() failed on listen socket");
                    apr_thread_yield();
                }
                continue;
            }

            /* remember the last_lr we searched last time around so that
            we don't end up starving any particular listening socket */
            if (last_lr == NULL) {
                lr = ap_listeners;
            }
            else {
                lr = last_lr->next;
                if (!lr)
                    lr = ap_listeners;
            }
            first_lr = lr;
            do {
                apr_os_sock_get(&sockdes, lr->sd);
                if (FD_ISSET(sockdes, &main_fds))
                    goto got_listener;
                lr = lr->next;
                if (!lr)
                    lr = ap_listeners;
            } while (lr != first_lr);
            /* if we get here, something unexpected happened. Go back
            into the select state and try again.
            */
            continue;
        got_listener:
            last_lr = lr;
            sd = lr->sd;

            wouldblock_retry = MAX_WB_RETRIES;

            while (wouldblock_retry) {
                if ((stat = apr_socket_accept(&csd, sd, ptrans)) == APR_SUCCESS) {
                    break;
                }
                else {
                    /* if the error is a wouldblock then maybe we were too
                        quick try to pull the next request from the listen
                        queue.  Try a few more times then return to our idle
                        listen state. */
                    if (!APR_STATUS_IS_EAGAIN(stat)) {
                        break;
                    }

                    if (wouldblock_retry--) {
                        apr_thread_yield();
                    }
                }
            }

            /* If we got a new socket, set it to non-blocking mode and process
                it.  Otherwise handle the error. */
            if (stat == APR_SUCCESS) {
                apr_socket_opt_set(csd, APR_SO_NONBLOCK, 0);
#ifdef DBINFO_ON
                if (wouldblock_retry < MAX_WB_RETRIES) {
                    retry_success++;
                    avg_retries += (MAX_WB_RETRIES-wouldblock_retry);
                }
#endif
                break;       /* We have a socket ready for reading */
            }
            else {
#ifdef DBINFO_ON
                if (APR_STATUS_IS_EAGAIN(stat)) {
                        would_block++;
                        retry_fail++;
                }
                else if (
#else
                if (APR_STATUS_IS_EAGAIN(stat) ||
#endif
                    APR_STATUS_IS_ECONNRESET(stat) ||
                    APR_STATUS_IS_ETIMEDOUT(stat) ||
                    APR_STATUS_IS_EHOSTUNREACH(stat) ||
                    APR_STATUS_IS_ENETUNREACH(stat)) {
                        ;
                }
#ifdef USE_WINSOCK
                else if (APR_STATUS_IS_ENETDOWN(stat)) {
                       /*
                        * When the network layer has been shut down, there
                        * is not much use in simply exiting: the parent
                        * would simply re-create us (and we'd fail again).
                        * Use the CHILDFATAL code to tear the server down.
                        * @@@ Martin's idea for possible improvement:
                        * A different approach would be to define
                        * a new APEXIT_NETDOWN exit code, the reception
                        * of which would make the parent shutdown all
                        * children, then idle-loop until it detected that
                        * the network is up again, and restart the children.
                        * Ben Hyde noted that temporary ENETDOWN situations
                        * occur in mobile IP.
                        */
                        ap_log_error(APLOG_MARK, APLOG_EMERG, stat, ap_server_conf,
                            "apr_socket_accept: giving up.");
                        clean_child_exit(APEXIT_CHILDFATAL, my_worker_num, ptrans,
                                         bucket_alloc);
                }
#endif
                else {
                        ap_log_error(APLOG_MARK, APLOG_ERR, stat, ap_server_conf,
                            "apr_socket_accept: (client socket)");
                        clean_child_exit(1, my_worker_num, ptrans, bucket_alloc);
                }
            }
        }

        ap_create_sb_handle(&sbh, ptrans, 0, my_worker_num);
        /*
        * We now have a connection, so set it up with the appropriate
        * socket options, file descriptors, and read/write buffers.
        */
        current_conn = ap_run_create_connection(ptrans, ap_server_conf, csd,
                                                my_worker_num, sbh,
                                                bucket_alloc);
        if (current_conn) {
            ap_process_connection(current_conn, csd);
            ap_lingering_close(current_conn);
        }
        request_count++;
    }
    clean_child_exit(0, my_worker_num, ptrans, bucket_alloc);
}
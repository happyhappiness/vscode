static void * APR_THREAD_FUNC listener_thread(apr_thread_t *thd, void * dummy)
{
    proc_info * ti = dummy;
    int process_slot = ti->pid;
    apr_pool_t *tpool = apr_thread_pool_get(thd);
    void *csd = NULL;
    apr_pool_t *ptrans = NULL;            /* Pool for per-transaction stuff */
    apr_pollset_t *pollset;
    apr_status_t rv;
    ap_listen_rec *lr;
    int have_idle_worker = 0;
    int last_poll_idx = 0;

    free(ti);

    rv = apr_pollset_create(&pollset, num_listensocks, tpool, 0);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "Couldn't create pollset in thread;"
                     " check system or user limits");
        /* let the parent decide how bad this really is */
        clean_child_exit(APEXIT_CHILDSICK);
    }

    for (lr = ap_listeners; lr != NULL; lr = lr->next) {
        apr_pollfd_t pfd = { 0 };

        pfd.desc_type = APR_POLL_SOCKET;
        pfd.desc.s = lr->sd;
        pfd.reqevents = APR_POLLIN;
        pfd.client_data = lr;

        rv = apr_pollset_add(pollset, &pfd);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                         "Couldn't create add listener to pollset;"
                         " check system or user limits");
            /* let the parent decide how bad this really is */
            clean_child_exit(APEXIT_CHILDSICK);
        }

        lr->accept_func = ap_unixd_accept;
    }

    /* Unblock the signal used to wake this thread up, and set a handler for
     * it.
     */
    unblock_signal(LISTENER_SIGNAL);
    apr_signal(LISTENER_SIGNAL, dummy_signal_handler);

    /* TODO: Switch to a system where threads reuse the results from earlier
       poll calls - manoj */
    while (1) {
        /* TODO: requests_this_child should be synchronized - aaron */
        if (requests_this_child <= 0) {
            check_infinite_requests();
        }
        if (listener_may_exit) break;

        if (!have_idle_worker) {
            /* the following pops a recycled ptrans pool off a stack
             * if there is one, in addition to reserving a worker thread
             */
            rv = ap_queue_info_wait_for_idler(worker_queue_info,
                                              &ptrans);
            if (APR_STATUS_IS_EOF(rv)) {
                break; /* we've been signaled to die now */
            }
            else if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_queue_info_wait failed. Attempting to "
                             " shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
                break;
            }
            have_idle_worker = 1;
        }

        /* We've already decremented the idle worker count inside
         * ap_queue_info_wait_for_idler. */

        if ((rv = SAFE_ACCEPT(apr_proc_mutex_lock(accept_mutex)))
            != APR_SUCCESS) {

            if (!listener_may_exit) {
                accept_mutex_error("lock", rv, process_slot);
            }
            break;                    /* skip the lock release */
        }

        if (!ap_listeners->next) {
            /* Only one listener, so skip the poll */
            lr = ap_listeners;
        }
        else {
            while (!listener_may_exit) {
                apr_int32_t numdesc;
                const apr_pollfd_t *pdesc;

                rv = apr_pollset_poll(pollset, -1, &numdesc, &pdesc);
                if (rv != APR_SUCCESS) {
                    if (APR_STATUS_IS_EINTR(rv)) {
                        continue;
                    }

                    /* apr_pollset_poll() will only return errors in catastrophic
                     * circumstances. Let's try exiting gracefully, for now. */
                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                                 "apr_pollset_poll: (listen)");
                    signal_threads(ST_GRACEFUL);
                }

                if (listener_may_exit) break;

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
                break;

            } /* while */

        } /* if/else */

        if (!listener_may_exit) {
            if (ptrans == NULL) {
                /* we can't use a recycled transaction pool this time.
                 * create a new transaction pool */
                apr_allocator_t *allocator;

                apr_allocator_create(&allocator);
                apr_allocator_max_free_set(allocator, ap_max_mem_free);
                apr_pool_create_ex(&ptrans, pconf, NULL, allocator);
                apr_allocator_owner_set(allocator, ptrans);
            }
            apr_pool_tag(ptrans, "transaction");
            rv = lr->accept_func(&csd, lr, ptrans);
            /* later we trash rv and rely on csd to indicate success/failure */
            AP_DEBUG_ASSERT(rv == APR_SUCCESS || !csd);

            if (rv == APR_EGENERAL) {
                /* E[NM]FILE, ENOMEM, etc */
                resource_shortage = 1;
                signal_threads(ST_GRACEFUL);
            }
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                != APR_SUCCESS) {

                if (listener_may_exit) {
                    break;
                }
                accept_mutex_error("unlock", rv, process_slot);
            }
            if (csd != NULL) {
                rv = ap_queue_push(worker_queue, csd, ptrans);
                if (rv) {
                    /* trash the connection; we couldn't queue the connected
                     * socket to a worker
                     */
                    apr_socket_close(csd);
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                                 "ap_queue_push failed");
                }
                else {
                    have_idle_worker = 0;
                }
            }
        }
        else {
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                != APR_SUCCESS) {
                int level = APLOG_EMERG;

                if (ap_scoreboard_image->parent[process_slot].generation !=
                    ap_scoreboard_image->global->running_generation) {
                    level = APLOG_DEBUG; /* common to get these at restart time */
                }
                ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to "
                             "shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
            }
            break;
        }
    }

    ap_close_listeners();
    ap_queue_term(worker_queue);
    dying = 1;
    ap_scoreboard_image->parent[process_slot].quiescing = 1;

    /* wake up the main thread */
    kill(ap_my_pid, SIGTERM);

    apr_thread_exit(thd, APR_SUCCESS);
    return NULL;
}
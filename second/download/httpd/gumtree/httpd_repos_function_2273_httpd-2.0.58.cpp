static void *listener_thread(apr_thread_t *thd, void * dummy)
{
    proc_info * ti = dummy;
    int process_slot = ti->pid;
    apr_pool_t *tpool = apr_thread_pool_get(thd);
    void *csd = NULL;
    apr_pool_t *ptrans;                /* Pool for per-transaction stuff */
    int n;
    apr_pollfd_t *pollset;
    apr_status_t rv;
    ap_listen_rec *lr, *last_lr = ap_listeners;
    worker_wakeup_info *worker = NULL;

    free(ti);

    apr_poll_setup(&pollset, num_listensocks, tpool);
    for(lr = ap_listeners ; lr != NULL ; lr = lr->next)
        apr_poll_socket_add(pollset, lr->sd, APR_POLLIN);

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

        if (worker == NULL) {
            rv = worker_stack_pop(idle_worker_stack, &worker);
            if (APR_STATUS_IS_EOF(rv)) {
                break;
            }
            else if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                             "worker_stack_pop failed");
                break;
            }
            ptrans = worker->pool;
        }
        AP_DEBUG_ASSERT(worker->state == WORKER_IDLE);

        if ((rv = SAFE_ACCEPT(apr_proc_mutex_lock(accept_mutex)))
            != APR_SUCCESS) {
            int level = APLOG_EMERG;

            if (listener_may_exit) {
                break;
            }
            if (ap_scoreboard_image->parent[process_slot].generation != 
                ap_scoreboard_image->global->running_generation) {
                level = APLOG_DEBUG; /* common to get these at restart time */
            }
            ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
                         "apr_proc_mutex_lock failed. Attempting to shutdown "
                         "process gracefully.");
            signal_threads(ST_GRACEFUL);
            break;                    /* skip the lock release */
        }

        if (!APR_O_NONBLOCK_INHERITED && !ap_listeners->next) {
            /* Only one listener, so skip the poll */
            lr = ap_listeners;
        }
        else {
            while (!listener_may_exit) {
                apr_status_t ret;
                apr_int16_t event;

                ret = apr_poll(pollset, num_listensocks, &n, -1);
                if (ret != APR_SUCCESS) {
                    if (APR_STATUS_IS_EINTR(ret)) {
                        continue;
                    }

                    /* apr_poll() will only return errors in catastrophic
                     * circumstances. Let's try exiting gracefully, for now. */
                    ap_log_error(APLOG_MARK, APLOG_ERR, ret, (const server_rec *)
                                 ap_server_conf, "apr_poll: (listen)");
                    signal_threads(ST_GRACEFUL);
                }

                if (listener_may_exit) break;

                /* find a listener */
                lr = last_lr;
                do {
                    lr = lr->next;
                    if (lr == NULL) {
                        lr = ap_listeners;
                    }
                    /* XXX: Should we check for POLLERR? */
                    apr_poll_revents_get(&event, lr->sd, pollset);
                    if (event & APR_POLLIN) {
                        last_lr = lr;
                        goto got_fd;
                    }
                } while (lr != last_lr);
            }
        }
    got_fd:
        if (!listener_may_exit) {
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
                int level = APLOG_EMERG;

                if (listener_may_exit) {
                    break;
                }
                if (ap_scoreboard_image->parent[process_slot].generation != 
                    ap_scoreboard_image->global->running_generation) {
                    level = APLOG_DEBUG; /* common to get these at restart time */
                }
                ap_log_error(APLOG_MARK, level, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to "
                             "shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
            }
            if (csd != NULL) {
                /* Wake up the sleeping worker. */
                apr_thread_mutex_lock(worker->mutex);
                worker->csd = (apr_socket_t *)csd;
                worker->state = WORKER_BUSY;
                /* Posix allows us to signal this condition without
                 * owning the associated mutex, but in that case it can
                 * not guarantee predictable scheduling. See
                 * _UNIX Network Programming: Interprocess Communication_
                 * by W. Richard Stevens, Vol 2, 2nd Ed, pp. 170-171. */
                apr_thread_cond_signal(worker->cond);
                apr_thread_mutex_unlock(worker->mutex);
                worker = NULL;
            }
        }
        else {
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(accept_mutex)))
                != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to "
                             "shutdown process gracefully.");
                signal_threads(ST_GRACEFUL);
            }
            break;
        }
    }

    workers_may_exit = 1;
    if (worker) {
        apr_thread_mutex_lock(worker->mutex);
        worker->state = WORKER_TERMINATED;
        /* Posix allows us to signal this condition without
         * owning the associated mutex, but in that case it can
         * not guarantee predictable scheduling. See
         * _UNIX Network Programming: Interprocess Communication_
         * by W. Richard Stevens, Vol 2, 2nd Ed, pp. 170-171. */
        apr_thread_cond_signal(worker->cond);
        apr_thread_mutex_unlock(worker->mutex);
    }
    worker_stack_terminate(idle_worker_stack);
    dying = 1;
    ap_scoreboard_image->parent[process_slot].quiescing = 1;

    /* wake up the main thread */
    kill(ap_my_pid, SIGTERM);

    apr_thread_exit(thd, APR_SUCCESS);
    return NULL;
}
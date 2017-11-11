static void *worker_thread(apr_thread_t *thd, void * dummy)
{
    proc_info * ti = dummy;
    int process_slot = ti->pid;
    int thread_slot = ti->tid;
    apr_uint32_t my_worker_num = (apr_uint32_t)(ti->tid);
    apr_pool_t *tpool = apr_thread_pool_get(thd);
    void *csd = NULL;
    apr_allocator_t *allocator;
    apr_pool_t *ptrans;                /* Pool for per-transaction stuff */
    apr_bucket_alloc_t *bucket_alloc;
    int n;
    apr_pollfd_t *pollset;
    apr_status_t rv;
    ap_listen_rec *lr, *last_lr = ap_listeners;
    int is_listener;

    ap_update_child_status_from_indexes(process_slot, thread_slot, SERVER_STARTING, NULL);

    free(ti);

    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    /* XXX: why is ptrans's parent not tpool?  --jcw 08/2003 */
    apr_pool_create_ex(&ptrans, NULL, NULL, allocator);
    apr_allocator_owner_set(allocator, ptrans);
    bucket_alloc = apr_bucket_alloc_create_ex(allocator);

    apr_poll_setup(&pollset, num_listensocks, tpool);
    for(lr = ap_listeners ; lr != NULL ; lr = lr->next)
        apr_poll_socket_add(pollset, lr->sd, APR_POLLIN);

    /* TODO: Switch to a system where threads reuse the results from earlier
       poll calls - manoj */
    is_listener = 0;
    while (!workers_may_exit) {

        ap_update_child_status_from_indexes(process_slot, thread_slot,
                                            SERVER_READY, NULL);
        if (!is_listener) {
            /* Wait until it's our turn to become the listener */
            if ((rv = worker_stack_wait(idle_worker_stack, my_worker_num)) !=
                APR_SUCCESS) {
                if (rv != APR_EINVAL) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                                 "worker_stack_wait failed. Shutting down");
                }
                break;
            }
            if (workers_may_exit) {
                break;
            }
            is_listener = 1;
        }

        /* TODO: requests_this_child should be synchronized - aaron */
        if (requests_this_child <= 0) {
            check_infinite_requests();
        }
        if (workers_may_exit) break;

        if ((rv = SAFE_ACCEPT(apr_proc_mutex_lock(accept_mutex)))
            != APR_SUCCESS) {
            int level = APLOG_EMERG;

            if (workers_may_exit) {
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

        if (!ap_listeners->next) {
            /* Only one listener, so skip the poll */
            lr = ap_listeners;
        }
        else {
            while (!workers_may_exit) {
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

                if (workers_may_exit) break;

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
        if (!workers_may_exit) {
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

                if (workers_may_exit) {
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
                is_listener = 0;
                worker_stack_awaken_next(idle_worker_stack);
                process_socket(ptrans, csd, process_slot,
                               thread_slot, bucket_alloc);
                apr_pool_clear(ptrans);
                requests_this_child--;
            }
            if ((ap_mpm_pod_check(pod) == APR_SUCCESS) ||
                (ap_my_generation !=
                 ap_scoreboard_image->global->running_generation)) {
                signal_threads(ST_GRACEFUL);
                break;
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

    dying = 1;
    ap_scoreboard_image->parent[process_slot].quiescing = 1;

    worker_stack_term(idle_worker_stack);

    ap_update_child_status_from_indexes(process_slot, thread_slot,
        (dying) ? SERVER_DEAD : SERVER_GRACEFUL, (request_rec *) NULL);

    apr_bucket_alloc_destroy(bucket_alloc);

    apr_thread_exit(thd, APR_SUCCESS);
    return NULL;
}
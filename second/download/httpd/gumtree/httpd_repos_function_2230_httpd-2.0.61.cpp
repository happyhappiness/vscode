static void *worker_thread(apr_thread_t *thd, void *arg)
{
    void *csd;
    apr_pool_t *tpool;      /* Pool for this thread           */
    apr_pool_t *ptrans;     /* Pool for per-transaction stuff */
    volatile int thread_just_started = 1;
    int srv;
    int thread_num = *((int *) arg);
    long conn_id = child_num * thread_limit + thread_num;
    apr_pollfd_t *pollset;
    apr_status_t rv;
    ap_listen_rec *lr, *last_lr = ap_listeners;
    int n;
    apr_bucket_alloc_t *bucket_alloc;

    apr_thread_mutex_lock(thread_pool_parent_mutex);
    apr_pool_create(&tpool, thread_pool_parent);
    apr_thread_mutex_unlock(thread_pool_parent_mutex);
    apr_pool_create(&ptrans, tpool);

    (void) ap_update_child_status_from_indexes(child_num, thread_num, 
                                               SERVER_STARTING,
                                               (request_rec *) NULL);

    bucket_alloc = apr_bucket_alloc_create(apr_thread_pool_get(thd));

    apr_poll_setup(&pollset, num_listensocks, tpool);
    for(lr = ap_listeners; lr != NULL; lr = lr->next) {
        int fd;
        apr_poll_socket_add(pollset, lr->sd, APR_POLLIN);

        apr_os_sock_get(&fd, lr->sd);
    }

    while (!workers_may_exit) {
        workers_may_exit |= ((ap_max_requests_per_child != 0)
                            && (requests_this_child <= 0));
        if (workers_may_exit) break;
        if (!thread_just_started) {
            apr_thread_mutex_lock(idle_thread_count_mutex);
            if (idle_thread_count < max_spare_threads) {
                idle_thread_count++;
                apr_thread_mutex_unlock(idle_thread_count_mutex);
            }
            else {
                apr_thread_mutex_unlock(idle_thread_count_mutex);
                break;
            }
        }
        else {
            thread_just_started = 0;
        }

        (void) ap_update_child_status_from_indexes(child_num, thread_num, 
                                                   SERVER_READY,
                                                   (request_rec *) NULL);

        apr_thread_mutex_lock(thread_accept_mutex);
        if (workers_may_exit) {
            apr_thread_mutex_unlock(thread_accept_mutex);
            break;
        }
        if ((rv = SAFE_ACCEPT(apr_proc_mutex_lock(process_accept_mutex)))
            != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                         "apr_proc_mutex_lock failed. Attempting to shutdown "
                         "process gracefully.");
            workers_may_exit = 1;
        }

        while (!workers_may_exit) {
            apr_int16_t event;
            srv = apr_poll(pollset, num_listensocks, &n, -1);

            if (srv != APR_SUCCESS) {
                if (APR_STATUS_IS_EINTR(srv)) {
                    continue;
                }

                /* apr_poll() will only return errors in catastrophic
                 * circumstances. Let's try exiting gracefully, for now. */
                ap_log_error(APLOG_MARK, APLOG_ERR, srv, (const server_rec *)
                             ap_server_conf, "apr_poll: (listen)");
                workers_may_exit = 1;
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
                if (event & (APR_POLLIN)) {
                    last_lr = lr;
                    goto got_fd;
                }
            } while (lr != last_lr);
        }
    got_fd:
        if (!workers_may_exit) {
            rv = lr->accept_func(&csd, lr, ptrans);
            if (rv == APR_EGENERAL) {
                /* E[NM]FILE, ENOMEM, etc */
                workers_may_exit = 1;
            }
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(process_accept_mutex)))
                != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to shutdown "
                             "process gracefully.");
                workers_may_exit = 1;
            }
            apr_thread_mutex_unlock(thread_accept_mutex);
            apr_thread_mutex_lock(idle_thread_count_mutex);
            if (idle_thread_count > min_spare_threads) {
                idle_thread_count--;
            }
            else {
                if (!start_thread()) {
                    idle_thread_count--;
                }
            }
            apr_thread_mutex_unlock(idle_thread_count_mutex);
            if (setjmp(jmpbuffer) != 1) {
                process_socket(ptrans, csd, conn_id, bucket_alloc);
            }
            else {
                thread_socket_table[thread_num] = AP_PERCHILD_THISCHILD;
            }  
            requests_this_child--;
        }
        else {
            if ((rv = SAFE_ACCEPT(apr_proc_mutex_unlock(process_accept_mutex)))
                != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                             "apr_proc_mutex_unlock failed. Attempting to shutdown "
                             "process gracefully.");
                workers_may_exit = 1;
            }
            apr_thread_mutex_unlock(thread_accept_mutex);
            apr_thread_mutex_lock(idle_thread_count_mutex);
            idle_thread_count--;
            apr_thread_mutex_unlock(idle_thread_count_mutex);
        break;
        }
        apr_pool_clear(ptrans);
    }

    apr_thread_mutex_lock(thread_pool_parent_mutex);
    ap_update_child_status_from_indexes(child_num, thread_num, SERVER_DEAD,
                                        (request_rec *) NULL);
    apr_pool_destroy(tpool);
    apr_thread_mutex_unlock(thread_pool_parent_mutex);
    apr_thread_mutex_lock(worker_thread_count_mutex);
    worker_thread_count--;
    worker_thread_free_ids[worker_thread_count] = thread_num;
    if (worker_thread_count == 0) {
        /* All the threads have exited, now finish the shutdown process
         * by signalling the sigwait thread */
        kill(my_pid, SIGTERM);
    }
    apr_thread_mutex_unlock(worker_thread_count_mutex);

    apr_bucket_alloc_destroy(bucket_alloc);

    return NULL;
}
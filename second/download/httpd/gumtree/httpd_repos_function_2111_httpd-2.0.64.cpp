static int32 worker_thread(void * dummy)
{
    proc_info * ti = dummy;
    int child_slot = ti->slot;
    apr_pool_t *tpool = ti->tpool;
    apr_allocator_t *allocator;
    apr_socket_t *csd = NULL;
    apr_pool_t *ptrans;		/* Pool for per-transaction stuff */
    apr_bucket_alloc_t *bucket_alloc;
    apr_socket_t *sd = NULL;
    apr_status_t rv = APR_EINIT;
    int srv , n;
    int curr_pollfd = 0, last_pollfd = 0;
    sigset_t sig_mask;
    int requests_this_child = ap_max_requests_per_thread;
    apr_pollfd_t *pollset;
    /* each worker thread is in control of its own destiny...*/
    int this_worker_should_exit = 0; 
    free(ti);

    mpm_state = AP_MPMQ_STARTING;

    on_exit_thread(check_restart, (void*)child_slot);
          
    /* block the signals for this thread */
    sigfillset(&sig_mask);
    sigprocmask(SIG_BLOCK, &sig_mask, NULL);

    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    apr_pool_create_ex(&ptrans, tpool, NULL, allocator);
    apr_allocator_owner_set(allocator, ptrans);

    apr_pool_tag(ptrans, "transaction");

    bucket_alloc = apr_bucket_alloc_create_ex(allocator);

    apr_thread_mutex_lock(worker_thread_count_mutex);
    worker_thread_count++;
    apr_thread_mutex_unlock(worker_thread_count_mutex);

    (void) ap_update_child_status_from_indexes(0, child_slot, SERVER_STARTING,
                                               (request_rec*)NULL);
                                  
    apr_poll_setup(&pollset, num_listening_sockets + 1, tpool);
    for(n=0 ; n <= num_listening_sockets ; n++)
        apr_poll_socket_add(pollset, listening_sockets[n], APR_POLLIN);

    mpm_state = AP_MPMQ_RUNNING;

    while (1) {
        /* If we're here, then chances are (unless we're the first thread created) 
         * we're going to be held up in the accept mutex, so doing this here
         * shouldn't hurt performance.
         */

        this_worker_should_exit |= (ap_max_requests_per_thread != 0) && (requests_this_child <= 0);
        
        if (this_worker_should_exit) break;

        (void) ap_update_child_status_from_indexes(0, child_slot, SERVER_READY,
                                                   (request_rec*)NULL);

        apr_thread_mutex_lock(accept_mutex);

        while (!this_worker_should_exit) {
            apr_int16_t event;
            apr_status_t ret;

            ret = apr_poll(pollset, num_listening_sockets + 1, &srv, -1);

            if (ret != APR_SUCCESS) {
                if (APR_STATUS_IS_EINTR(ret)) {
                    continue;
                }
                /* poll() will only return errors in catastrophic
                 * circumstances. Let's try exiting gracefully, for now. */
                ap_log_error(APLOG_MARK, APLOG_ERR, ret, (const server_rec *)
                             ap_server_conf, "apr_poll: (listen)");
                this_worker_should_exit = 1;
            } else {
                /* if we've bailed in apr_poll what's the point of trying to use the data? */
                apr_poll_revents_get(&event, listening_sockets[0], pollset);

                if (event & APR_POLLIN){
                    apr_sockaddr_t *rec_sa;
                    apr_size_t len = 5;
                    char *tmpbuf = apr_palloc(ptrans, sizeof(char) * 5);
                    apr_sockaddr_info_get(&rec_sa, "127.0.0.1", APR_UNSPEC, 7772, 0, ptrans);
                    
                    if ((ret = apr_recvfrom(rec_sa, listening_sockets[0], 0, tmpbuf, &len))
                        != APR_SUCCESS){
                        ap_log_error(APLOG_MARK, APLOG_ERR, ret, NULL, 
                            "error getting data from UDP!!");
                    }else {
                        /* add checking??? */              
                    }
                    this_worker_should_exit = 1;
                }
            }
          
            if (this_worker_should_exit) break;

            if (num_listening_sockets == 1) {
                sd = ap_listeners->sd;
                goto got_fd;
            }
            else {
                /* find a listener */
                curr_pollfd = last_pollfd;
                do {
                    curr_pollfd++;

                    if (curr_pollfd > num_listening_sockets)
                        curr_pollfd = 1;
                    
                    /* Get the revent... */
                    apr_poll_revents_get(&event, listening_sockets[curr_pollfd], pollset);
                    
                    if (event & APR_POLLIN) {
                        last_pollfd = curr_pollfd;
                        sd = listening_sockets[curr_pollfd];
                        goto got_fd;
                    }
                } while (curr_pollfd != last_pollfd);
            }
        }
    got_fd:

        if (!this_worker_should_exit) {
            rv = apr_accept(&csd, sd, ptrans);

            apr_thread_mutex_unlock(accept_mutex);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                  "apr_accept");
            } else {
                process_socket(ptrans, csd, child_slot, bucket_alloc);
                requests_this_child--;
            }
        }
        else {
            apr_thread_mutex_unlock(accept_mutex);
            break;
        }
        apr_pool_clear(ptrans);
    }

    ap_update_child_status_from_indexes(0, child_slot, SERVER_DEAD, (request_rec*)NULL);

    apr_bucket_alloc_destroy(bucket_alloc);

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, NULL,
                 "worker_thread %ld exiting", find_thread(NULL));
    
    apr_thread_mutex_lock(worker_thread_count_mutex);
    worker_thread_count--;
    apr_thread_mutex_unlock(worker_thread_count_mutex);

    return (0);
}
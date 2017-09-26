/*****************************************************************
 * Here follows a long bunch of generic server bookkeeping stuff...
 */

int ap_graceful_stop_signalled(void)
{
    /* XXX - Does this really work? - Manoj */
    return is_graceful;
}

/*****************************************************************
 * Child process main loop.
 */

static void process_socket(apr_pool_t *p, apr_socket_t *sock,
                           int my_child_num, apr_bucket_alloc_t *bucket_alloc)
{
    conn_rec *current_conn;
    long conn_id = my_child_num;
    int csd;
    ap_sb_handle_t *sbh;

    (void)apr_os_sock_get(&csd, sock);
    
    if (csd >= FD_SETSIZE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
                     "filedescriptor (%u) larger than FD_SETSIZE (%u) "
                     "found, you probably need to rebuild Apache with a "
                     "larger FD_SETSIZE", csd, FD_SETSIZE);
        apr_socket_close(sock);
        return;
    }

    ap_create_sb_handle(&sbh, p, 0, my_child_num);
    current_conn = ap_run_create_connection(p, ap_server_conf,
                                            sock, conn_id, sbh,
                                            bucket_alloc);

    if (current_conn) {
        ap_process_connection(current_conn, sock);
        ap_lingering_close(current_conn);
    }
}

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

static int make_worker(int slot)
{
    thread_id tid;
    proc_info *my_info = (proc_info *)malloc(sizeof(proc_info)); /* freed by thread... */

    if (my_info == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, errno, ap_server_conf,
            "malloc: out of memory");
        clean_child_exit(APEXIT_CHILDFATAL);
    }
    
    my_info->slot = slot;
    apr_pool_create(&my_info->tpool, pchild);
    
    if (slot + 1 > ap_max_child_assigned)
	    ap_max_child_assigned = slot + 1;

    if (one_process) {
    	set_signals();
        ap_scoreboard_image->parent[0].pid = getpid();
        return 0;
    }

    (void) ap_update_child_status_from_indexes(0, slot, SERVER_STARTING, (request_rec*)NULL);
    tid = spawn_thread(worker_thread, "apache_worker", B_NORMAL_PRIORITY,
        my_info);
    if (tid < B_NO_ERROR) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, NULL, 
            "spawn_thread: Unable to start a new thread");
        /* In case system resources are maxxed out, we don't want
         * Apache running away with the CPU trying to fork over and
         * over and over again. 
         */
        (void) ap_update_child_status_from_indexes(0, slot, SERVER_DEAD, 
                                                   (request_rec*)NULL);
        
    	sleep(10);
        free(my_info);
        
    	return -1;
    }
    resume_thread(tid);

    ap_scoreboard_image->servers[0][slot].tid = tid;
    return 0;
}

static void check_restart(void *data)
{
    if (!restart_pending && !shutdown_pending) {
        int slot = (int)data;
        make_worker(slot);
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, 
            "spawning a new worker thread in slot %d", slot);
    }
}

/* start up a bunch of children */
static void startup_threads(int number_to_start)
{
    int i;

    for (i = 0; number_to_start && i < ap_thread_limit; ++i) {
	if (ap_scoreboard_image->servers[0][i].tid) {
	    continue;
	}
	if (make_worker(i) < 0) {
	    break;
	}
	--number_to_start;
    }
}


/*

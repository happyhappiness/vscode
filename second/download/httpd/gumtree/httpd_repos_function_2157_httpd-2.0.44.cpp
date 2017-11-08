static void child_main(int child_num_arg)
{
    int i;
    apr_status_t rv;
    apr_socket_t *sock = NULL;
    ap_listen_rec *lr;
    
    my_pid = getpid();
    child_num = child_num_arg;
    apr_pool_create(&pchild, pconf);

    for (lr = ap_listeners ; lr->next != NULL; lr = lr->next) {
        continue;
    }

    apr_os_sock_put(&sock, &child_info_table[child_num].input, pconf);
    lr->next = apr_palloc(pconf, sizeof(*lr));
    lr->next->sd = sock;
    lr->next->active = 1;
    lr->next->accept_func = receive_from_other_child;
    lr->next->next = NULL;
    lr = lr->next;
    num_listensocks++;

    /*stuff to do before we switch id's, so we have permissions.*/

    rv = SAFE_ACCEPT(apr_proc_mutex_child_init(&process_accept_mutex, 
                                               ap_lock_fname, pchild));
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ap_server_conf,
                     "Couldn't initialize cross-process lock in child");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    if (perchild_setup_child(child_num)) {
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    ap_run_child_init(pchild, ap_server_conf);

    /*done with init critical section */

    apr_setup_signal_thread();

    requests_this_child = ap_max_requests_per_child;
    

    /* Setup worker threads */

    if (threads_to_start > max_threads) {
        threads_to_start = max_threads;
    }
    idle_thread_count = threads_to_start;
    worker_thread_count = 0;
    worker_thread_free_ids = (int *)apr_pcalloc(pchild, thread_limit * sizeof(int));
    for (i = 0; i < max_threads; i++) {
        worker_thread_free_ids[i] = i;
    }
    apr_pool_create(&thread_pool_parent, pchild);
    apr_thread_mutex_create(&thread_pool_parent_mutex, 
                    APR_THREAD_MUTEX_DEFAULT, pchild);
    apr_thread_mutex_create(&idle_thread_count_mutex, 
                    APR_THREAD_MUTEX_DEFAULT, pchild);
    apr_thread_mutex_create(&worker_thread_count_mutex,
                    APR_THREAD_MUTEX_DEFAULT, pchild);
    apr_thread_mutex_create(&pipe_of_death_mutex,
                    APR_THREAD_MUTEX_DEFAULT, pchild);
    apr_thread_mutex_create(&thread_accept_mutex,
                    APR_THREAD_MUTEX_DEFAULT, pchild);

    apr_threadattr_create(&worker_thread_attr, pchild);
    apr_threadattr_detach_set(worker_thread_attr, 1);                                     

    /* We are creating worker threads right now */
    for (i=0; i < threads_to_start; i++) {
        /* start_thread shouldn't fail here */
        if (!start_thread()) {
            break;
        }
    }

    apr_signal_thread(check_signal);
}
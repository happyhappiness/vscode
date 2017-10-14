static void * APR_THREAD_FUNC start_threads(apr_thread_t *thd, void *dummy)
{
    thread_starter *ts = dummy;
    apr_thread_t **threads = ts->threads;
    apr_threadattr_t *thread_attr = ts->threadattr;
    int child_num_arg = ts->child_num_arg;
    int my_child_num = child_num_arg;
    proc_info *my_info;
    apr_status_t rv;
    int i;
    int threads_created = 0;
    int loops;
    int prev_threads_created;

    idle_worker_stack = worker_stack_create(pchild, ap_threads_per_child);
    if (idle_worker_stack == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, ap_server_conf,
                     "worker_stack_create() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    worker_wakeups = (worker_wakeup_info **)
        apr_palloc(pchild, sizeof(worker_wakeup_info *) *
                   ap_threads_per_child);

    loops = prev_threads_created = 0;
    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int status = ap_scoreboard_image->servers[child_num_arg][i].status;
            worker_wakeup_info *wakeup;

            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
            }

            wakeup = worker_wakeup_create(pchild);
            if (wakeup == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, 0,
                             ap_server_conf, "worker_wakeup_create failed");
                clean_child_exit(APEXIT_CHILDFATAL);
            }
            worker_wakeups[threads_created] = wakeup;
            my_info = (proc_info *)malloc(sizeof(proc_info));
            if (my_info == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT, errno, ap_server_conf,
                             "malloc: out of memory");
                clean_child_exit(APEXIT_CHILDFATAL);
            }
            my_info->pid = my_child_num;
            my_info->tid = i;
            my_info->sd = 0;
        
            /* We are creating threads right now */
            ap_update_child_status_from_indexes(my_child_num, i,
                                                SERVER_STARTING, NULL);
            /* We let each thread update its own scoreboard entry.  This is
             * done because it lets us deal with tid better.
             */
            rv = apr_thread_create(&threads[i], thread_attr, 
                                   worker_thread, my_info, pchild);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                    "apr_thread_create: unable to create worker thread");
                /* In case system resources are maxxed out, we don't want
                   Apache running away with the CPU trying to fork over and
                   over and over again if we exit. */
                apr_sleep(10 * APR_USEC_PER_SEC);
                clean_child_exit(APEXIT_CHILDFATAL);
            }
            threads_created++;
        }
        if (start_thread_may_exit || threads_created == ap_threads_per_child) {
            break;
        }
        /* wait for previous generation to clean up an entry */
        apr_sleep(1 * APR_USEC_PER_SEC);
        ++loops;
        if (loops % 120 == 0) { /* every couple of minutes */
            if (prev_threads_created == threads_created) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                             "child %" APR_PID_T_FMT " isn't taking over "
                             "slots very quickly (%d of %d)",
                             ap_my_pid, threads_created, ap_threads_per_child);
            }
            prev_threads_created = threads_created;
        }
    }
    
    /* What state should this child_main process be listed as in the 
     * scoreboard...?
     *  ap_update_child_status_from_indexes(my_child_num, i, SERVER_STARTING, 
     *                                      (request_rec *) NULL);
     * 
     *  This state should be listed separately in the scoreboard, in some kind
     *  of process_status, not mixed in with the worker threads' status.   
     *  "life_status" is almost right, but it's in the worker's structure, and 
     *  the name could be clearer.   gla
     */
    apr_thread_exit(thd, APR_SUCCESS);
    return NULL;
}
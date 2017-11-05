void child_main(apr_pool_t *pconf, DWORD parent_pid)
{
    apr_status_t status;
    apr_hash_t *ht;
    ap_listen_rec *lr;
    HANDLE child_events[3];
    HANDLE *child_handles;
    int listener_started = 0;
    int threads_created = 0;
    int watch_thread;
    int time_remains;
    int cld;
    DWORD tid;
    int rv;
    int i;
    int num_events;

    apr_pool_create(&pchild, pconf);
    apr_pool_tag(pchild, "pchild");

    ap_run_child_init(pchild, ap_server_conf);
    ht = apr_hash_make(pchild);

    /* Initialize the child_events */
    max_requests_per_child_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!max_requests_per_child_event) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00350)
                     "Child: Failed to create a max_requests event.");
        exit(APEXIT_CHILDINIT);
    }
    child_events[0] = exit_event;
    child_events[1] = max_requests_per_child_event;

    if (parent_pid != my_pid) {
        child_events[2] = OpenProcess(SYNCHRONIZE, FALSE, parent_pid);
        if (child_events[2] == NULL) {
            num_events = 2;
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf, APLOGNO(02643)
                         "Child: Failed to open handle to parent process %ld; "
                         "will not react to abrupt parent termination", parent_pid);
        }
        else {
            num_events = 3;
        }
    }
    else {
        /* presumably -DONE_PROCESS */
        child_events[2] = NULL;
        num_events = 2;
    }

    /*
     * Wait until we have permission to start accepting connections.
     * start_mutex is used to ensure that only one child ever
     * goes into the listen/accept loop at once.
     */
    status = apr_proc_mutex_lock(start_mutex);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf, APLOGNO(00351)
                     "Child: Failed to acquire the start_mutex. "
                     "Process will exit.");
        exit(APEXIT_CHILDINIT);
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00352)
                 "Child: Acquired the start mutex.");

    /*
     * Create the worker thread dispatch IOCompletionPort
     */
    /* Create the worker thread dispatch IOCP */
    ThreadDispatchIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
                                                NULL, 0, 0);
    apr_thread_mutex_create(&qlock, APR_THREAD_MUTEX_DEFAULT, pchild);
    qwait_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!qwait_event) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
                     ap_server_conf, APLOGNO(00353)
                     "Child: Failed to create a qwait event.");
        exit(APEXIT_CHILDINIT);
    }

    /*
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00354)
                 "Child: Starting %d worker threads.", ap_threads_per_child);
    child_handles = (HANDLE) apr_pcalloc(pchild, ap_threads_per_child
                                                  * sizeof(HANDLE));
    apr_thread_mutex_create(&child_lock, APR_THREAD_MUTEX_DEFAULT, pchild);

    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int *score_idx;
            int status = ap_scoreboard_image->servers[0][i].status;
            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
            }
            ap_update_child_status_from_indexes(0, i, SERVER_STARTING, NULL);

            child_handles[i] = CreateThread(NULL, ap_thread_stacksize,
                                            worker_main, (void *) i,
                                            stack_res_flag, &tid);
            if (child_handles[i] == 0) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
                             ap_server_conf, APLOGNO(00355)
                             "Child: CreateThread failed. Unable to "
                             "create all worker threads. Created %d of the %d "
                             "threads requested with the ThreadsPerChild "
                             "configuration directive.",
                             threads_created, ap_threads_per_child);
                ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
                goto shutdown;
            }
            threads_created++;
            /* Save the score board index in ht keyed to the thread handle.
             * We need this when cleaning up threads down below...
             */
            apr_thread_mutex_lock(child_lock);
            score_idx = apr_pcalloc(pchild, sizeof(int));
            *score_idx = i;
            apr_hash_set(ht, &child_handles[i], sizeof(HANDLE), score_idx);
            apr_thread_mutex_unlock(child_lock);
        }
        /* Start the listener only when workers are available */
        if (!listener_started && threads_created) {
            create_listener_thread();
            listener_started = 1;
            winnt_mpm_state = AP_MPMQ_RUNNING;
        }
        if (threads_created == ap_threads_per_child) {
            break;
        }
        /* Check to see if the child has been told to exit */
        if (WaitForSingleObject(exit_event, 0) != WAIT_TIMEOUT) {
            break;
        }
        /* wait for previous generation to clean up an entry in the scoreboard
         */
        apr_sleep(1 * APR_USEC_PER_SEC);
    }

    /* Wait for one of these events:
     * exit_event:
     *    The exit_event is signaled by the parent process to notify
     *    the child that it is time to exit.
     *
     * max_requests_per_child_event:
     *    This event is signaled by the worker threads to indicate that
     *    the process has handled MaxConnectionsPerChild connections.
     *
     * parent process exiting
     *
     * TIMEOUT:
     *    To do periodic maintenance on the server (check for thread exits,
     *    number of completion contexts, etc.)
     *
     * XXX: thread exits *aren't* being checked.
     *
     * XXX: other_child - we need the process handles to the other children
     *      in order to map them to apr_proc_other_child_read (which is not
     *      named well, it's more like a_p_o_c_died.)
     *
     * XXX: however - if we get a_p_o_c handle inheritance working, and
     *      the parent process creates other children and passes the pipes
     *      to our worker processes, then we have no business doing such
     *      things in the child_main loop, but should happen in master_main.
     */
    while (1) {
#if !APR_HAS_OTHER_CHILD
        rv = WaitForMultipleObjects(num_events, (HANDLE *)child_events, FALSE, INFINITE);
        cld = rv - WAIT_OBJECT_0;
#else
        /* THIS IS THE EXPECTED BUILD VARIATION -- APR_HAS_OTHER_CHILD */
        rv = WaitForMultipleObjects(num_events, (HANDLE *)child_events, FALSE, 1000);
        cld = rv - WAIT_OBJECT_0;
        if (rv == WAIT_TIMEOUT) {
            apr_proc_other_child_refresh_all(APR_OC_REASON_RUNNING);
        }
        else
#endif
            if (rv == WAIT_FAILED) {
            /* Something serious is wrong */
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
                         ap_server_conf, APLOGNO(00356)
                         "Child: WAIT_FAILED -- shutting down server");
            /* check handle validity to identify a possible culprit */
            for (i = 0; i < num_events; i++) {
                DWORD out_flags;

                if (0 == GetHandleInformation(child_events[i], &out_flags)) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
                                 ap_server_conf, APLOGNO(02644)
                                 "Child: Event handle #%d (%pp) is invalid",
                                 i, child_events[i]);
                }
            }
            break;
        }
        else if (cld == 0) {
            /* Exit event was signaled */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00357)
                         "Child: Exit event signaled. Child process is "
                         "ending.");
            break;
        }
        else if (cld == 2) {
            /* The parent is dead.  Shutdown the child process. */
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(02538)
                         "Child: Parent process exited abruptly. Child process "
                         "is ending");
            break;
        }
        else {
            /* MaxConnectionsPerChild event set by the worker threads.
             * Signal the parent to restart
             */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00358)
                         "Child: Process exiting because it reached "
                         "MaxConnectionsPerChild. Signaling the parent to "
                         "restart a new child process.");
            ap_signal_parent(SIGNAL_PARENT_RESTART);
            break;
        }
    }

    /*
     * Time to shutdown the child process
     */

 shutdown:

    winnt_mpm_state = AP_MPMQ_STOPPING;

    /* Close the listening sockets. Note, we must close the listeners
     * before closing any accept sockets pending in AcceptEx to prevent
     * memory leaks in the kernel.
     */
    for (lr = ap_listeners; lr ; lr = lr->next) {
        apr_socket_close(lr->sd);
    }

    /* Shutdown listener threads and pending AcceptEx sockets
     * but allow the worker threads to continue consuming from
     * the queue of accepted connections.
     */
    shutdown_in_progress = 1;

    Sleep(1000);

    /* Tell the worker threads to exit */
    workers_may_exit = 1;

    /* Release the start_mutex to let the new process (in the restart
     * scenario) a chance to begin accepting and servicing requests
     */
    rv = apr_proc_mutex_unlock(start_mutex);
    if (rv == APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf, APLOGNO(00359)
                     "Child: Released the start mutex");
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf, APLOGNO(00360)
                     "Child: Failure releasing the start mutex");
    }

    /* Shutdown the worker threads
     * Post worker threads blocked on the ThreadDispatch IOCompletion port
     */
    while (g_blocked_threads > 0) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00361)
                     "Child: %d threads blocked on the completion port",
                     g_blocked_threads);
        for (i=g_blocked_threads; i > 0; i--) {
            PostQueuedCompletionStatus(ThreadDispatchIOCP, 0,
                                       IOCP_SHUTDOWN, NULL);
        }
        Sleep(1000);
    }
    /* Empty the accept queue of completion contexts */
    apr_thread_mutex_lock(qlock);
    while (qhead) {
        CloseHandle(qhead->overlapped.hEvent);
        closesocket(qhead->accept_socket);
        qhead = qhead->next;
    }
    apr_thread_mutex_unlock(qlock);

    /* Give busy threads a chance to service their connections
     * (no more than the global server timeout period which
     * we track in msec remaining).
     */
    watch_thread = 0;
    time_remains = (int)(ap_server_conf->timeout / APR_TIME_C(1000));

    while (threads_created)
    {
        int nFailsafe = MAXIMUM_WAIT_OBJECTS;
        DWORD dwRet;

        /* Every time we roll over to wait on the first group
         * of MAXIMUM_WAIT_OBJECTS threads, take a breather,
         * and infrequently update the error log.
         */
        if (watch_thread >= threads_created) {
            if ((time_remains -= 100) < 0)
                break;

            /* Every 30 seconds give an update */
            if ((time_remains % 30000) == 0) {
                ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS,
                             ap_server_conf, APLOGNO(00362)
                             "Child: Waiting %d more seconds "
                             "for %d worker threads to finish.",
                             time_remains / 1000, threads_created);
            }
            /* We'll poll from the top, 10 times per second */
            Sleep(100);
            watch_thread = 0;
        }

        /* Fairness, on each iteration we will pick up with the thread
         * after the one we just removed, even if it's a single thread.
         * We don't block here.
         */
        dwRet = WaitForMultipleObjects(min(threads_created - watch_thread,
                                           MAXIMUM_WAIT_OBJECTS),
                                       child_handles + watch_thread, 0, 0);

        if (dwRet == WAIT_FAILED) {
            break;
        }
        if (dwRet == WAIT_TIMEOUT) {
            /* none ready */
            watch_thread += MAXIMUM_WAIT_OBJECTS;
            continue;
        }
        else if (dwRet >= WAIT_ABANDONED_0) {
            /* We just got the ownership of the object, which
             * should happen at most MAXIMUM_WAIT_OBJECTS times.
             * It does NOT mean that the object is signaled.
             */
            if ((nFailsafe--) < 1)
                break;
        }
        else {
            watch_thread += (dwRet - WAIT_OBJECT_0);
            if (watch_thread >= threads_created)
                break;
            cleanup_thread(child_handles, &threads_created, watch_thread);
        }
    }

    /* Kill remaining threads off the hard way */
    if (threads_created) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00363)
                     "Child: Terminating %d threads that failed to exit.",
                     threads_created);
    }
    for (i = 0; i < threads_created; i++) {
        int *score_idx;
        TerminateThread(child_handles[i], 1);
        CloseHandle(child_handles[i]);
        /* Reset the scoreboard entry for the thread we just whacked */
        score_idx = apr_hash_get(ht, &child_handles[i], sizeof(HANDLE));
        if (score_idx) {
            ap_update_child_status_from_indexes(0, *score_idx, SERVER_DEAD, NULL);
        }
    }
    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00364)
                 "Child: All worker threads have exited.");

    apr_thread_mutex_destroy(child_lock);
    apr_thread_mutex_destroy(qlock);
    CloseHandle(qwait_event);

    apr_pool_destroy(pchild);
    CloseHandle(exit_event);
    if (child_events[2] != NULL) {
        CloseHandle(child_events[2]);
    }
}
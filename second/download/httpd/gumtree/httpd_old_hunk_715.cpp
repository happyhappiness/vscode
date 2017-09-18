                        &WSAProtocolInfo, 0, 0);
        if (nsd == INVALID_SOCKET) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf,
                         "Child %d: setup_inherited_listeners(), WSASocket failed to open the inherited socket.", my_pid);
            exit(APEXIT_CHILDINIT);
        }
        apr_os_sock_put(&lr->sd, &nsd, s->process->pool);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 "Child %d: retrieved %d listeners from parent", my_pid, lcnt);

    if (!set_listeners_noninheritable(s->process->pool)) {
        exit(APEXIT_CHILDINIT);
    }
}


/* Windows 9x specific code...
 * Accept processing for on Windows 95/98 uses a producer/consumer queue 
 * model. A single thread accepts connections and queues the accepted socket 
 * to the accept queue for consumption by a pool of worker threads.
 *
 * win9x_accept()
 *    The accept threads runs this function, which accepts connections off 
 *    the network and calls add_job() to queue jobs to the accept_queue.
 * add_job()/remove_job()
 *    Add or remove an accepted socket from the list of sockets 
 *    connected to clients. allowed_globals.jobmutex protects
 *    against multiple concurrent access to the linked list of jobs.
 * win9x_get_connection()
 *    Calls remove_job() to pull a job from the accept queue. All the worker 
 *    threads block on remove_job.
 */

typedef struct joblist_s {
    struct joblist_s *next;
    int sock;
} joblist;

typedef struct globals_s {
    HANDLE jobsemaphore;
    joblist *jobhead;
    joblist *jobtail;
    apr_thread_mutex_t *jobmutex;
    int jobcount;
} globals;

globals allowed_globals = {NULL, NULL, NULL, NULL, 0};
#define MAX_SELECT_ERRORS 100

static void add_job(int sock)
{
    joblist *new_job;

    new_job = (joblist *) malloc(sizeof(joblist));
    if (new_job == NULL) {
	ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, 
                     "Ouch!  Out of memory in add_job()!");
        return;
    }
    new_job->next = NULL;
    new_job->sock = sock;

    apr_thread_mutex_lock(allowed_globals.jobmutex);

    if (allowed_globals.jobtail != NULL)
	allowed_globals.jobtail->next = new_job;
    allowed_globals.jobtail = new_job;
    if (!allowed_globals.jobhead)
	allowed_globals.jobhead = new_job;
    allowed_globals.jobcount++;
    ReleaseSemaphore(allowed_globals.jobsemaphore, 1, NULL);

    apr_thread_mutex_unlock(allowed_globals.jobmutex);
}

static int remove_job(void)
{
    joblist *job;
    int sock;

    WaitForSingleObject(allowed_globals.jobsemaphore, INFINITE);
    apr_thread_mutex_lock(allowed_globals.jobmutex);

    if (shutdown_in_progress && !allowed_globals.jobhead) {
        apr_thread_mutex_unlock(allowed_globals.jobmutex);
	return (-1);
    }
    job = allowed_globals.jobhead;
    ap_assert(job);
    allowed_globals.jobhead = job->next;
    if (allowed_globals.jobhead == NULL)
	allowed_globals.jobtail = NULL;
    apr_thread_mutex_unlock(allowed_globals.jobmutex);
    sock = job->sock;
    free(job);

    return (sock);
}

static void win9x_accept(void * dummy)
{
    struct timeval tv;
    fd_set main_fds;
    int wait_time = 1;
    int csd;
    SOCKET nsd = INVALID_SOCKET;
    struct sockaddr_in sa_client;
    int count_select_errors = 0;
    int rc;
    int clen;
    ap_listen_rec *lr;
    struct fd_set listenfds;
    SOCKET listenmaxfd = INVALID_SOCKET;

    /* Setup the listeners 
     * ToDo: Use apr_poll()
     */
    FD_ZERO(&listenfds);
    for (lr = ap_listeners; lr; lr = lr->next) {
        if (lr->sd != NULL) {
            apr_os_sock_get(&nsd, lr->sd);
            FD_SET(nsd, &listenfds);
            if (listenmaxfd == INVALID_SOCKET || nsd > listenmaxfd) {
                listenmaxfd = nsd;
            }
        }
    }
    head_listener = ap_listeners;

    while (!shutdown_in_progress) {
	tv.tv_sec = wait_time;
	tv.tv_usec = 0;
	memcpy(&main_fds, &listenfds, sizeof(fd_set));

	rc = select(listenmaxfd + 1, &main_fds, NULL, NULL, &tv);

        if (rc == 0 || (rc == SOCKET_ERROR && APR_STATUS_IS_EINTR(apr_get_netos_error()))) {
            count_select_errors = 0;    /* reset count of errors */            
            continue;
        }
        else if (rc == SOCKET_ERROR) {
            /* A "real" error occurred, log it and increment the count of
             * select errors. This count is used to ensure we don't go into
             * a busy loop of continuous errors.
             */
            ap_log_error(APLOG_MARK, APLOG_INFO, apr_get_netos_error(), ap_server_conf, 
                         "select failed with error %d", apr_get_netos_error());
            count_select_errors++;
            if (count_select_errors > MAX_SELECT_ERRORS) {
                shutdown_in_progress = 1;
                ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(), ap_server_conf,
                             "Too many errors in select loop. Child process exiting.");
                break;
            }
	} else {
	    ap_listen_rec *lr;

	    lr = find_ready_listener(&main_fds);
	    if (lr != NULL) {
                /* fetch the native socket descriptor */
                apr_os_sock_get(&nsd, lr->sd);
	    }
	}

	do {
            clen = sizeof(sa_client);
            csd = accept(nsd, (struct sockaddr *) &sa_client, &clen);
            if (csd == INVALID_SOCKET) {
                csd = -1;
            }
        } while (csd < 0 && APR_STATUS_IS_EINTR(apr_get_netos_error()));

	if (csd < 0) {
            if (APR_STATUS_IS_ECONNABORTED(apr_get_netos_error())) {
		ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(), ap_server_conf,
			    "accept: (client socket)");
            }
	}
	else {
	    add_job(csd);
	}
    }
    SetEvent(exit_event);
}

static PCOMP_CONTEXT win9x_get_connection(PCOMP_CONTEXT context)
{
    apr_os_sock_info_t sockinfo;
    int len;

    if (context == NULL) {
        /* allocate the completion context and the transaction pool */
        context = apr_pcalloc(pconf, sizeof(COMP_CONTEXT));
        apr_pool_create(&context->ptrans, pchild);
        apr_pool_tag(context->ptrans, "ptrans");
        context->ba = apr_bucket_alloc_create(pchild);
    }
    
    while (1) {
        apr_pool_clear(context->ptrans);        
        context->accept_socket = remove_job();
        if (context->accept_socket == -1) {
            return NULL;
        }
	len = sizeof(struct sockaddr);
        context->sa_server = apr_palloc(context->ptrans, len);
        if (getsockname(context->accept_socket, 
                        context->sa_server, &len)== SOCKET_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf, 
                         "getsockname failed");
            continue;
        }
        len = sizeof(struct sockaddr);
        context->sa_client = apr_palloc(context->ptrans, len);
        if ((getpeername(context->accept_socket,
                         context->sa_client, &len)) == SOCKET_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf, 
                         "getpeername failed");
            memset(&context->sa_client, '\0', sizeof(context->sa_client));
        }
        sockinfo.os_sock = &context->accept_socket;
        sockinfo.local   = context->sa_server;
        sockinfo.remote  = context->sa_client;
        sockinfo.family  = APR_INET;
        sockinfo.type    = SOCK_STREAM;
        apr_os_sock_make(&context->sock, &sockinfo, context->ptrans);

        return context;
    }
}
/* Windows NT/2000 specific code...
 * Accept processing for on Windows NT uses a producer/consumer queue 
 * model. An accept thread accepts connections off the network then issues
 * PostQueuedCompletionStatus() to awake a thread blocked on the ThreadDispatch 
 * IOCompletionPort.
 *
 * winnt_accept()
 *    One or more accept threads run in this function, each of which accepts 
 *    connections off the network and calls PostQueuedCompletionStatus() to
 *    queue an io completion packet to the ThreadDispatch IOCompletionPort.
 * winnt_get_connection()
 *    Worker threads block on the ThreadDispatch IOCompletionPort awaiting 
 *    connections to service.
 */
static void winnt_accept(void *lr_) 
{
    ap_listen_rec *lr = (ap_listen_rec *)lr_;
    apr_os_sock_info_t sockinfo;
    PCOMP_CONTEXT context = NULL;
    DWORD BytesRead;
    SOCKET nlsd;
    int rv;

    apr_os_sock_get(&nlsd, lr->sd);

    while (!shutdown_in_progress) {
        if (!context) {
            context = mpm_get_completion_context();
            if (!context) {
                /* Temporary resource constraint? */
                Sleep(0);
                continue;
            }
        }

        /* Create and initialize the accept socket */
        if (context->accept_socket == INVALID_SOCKET) {
            context->accept_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (context->accept_socket == INVALID_SOCKET) {
                /* Another temporary condition? */
                ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                             "winnt_accept: Failed to allocate an accept socket. "
                             "Temporary resource constraint? Try again.");
                Sleep(100);
                continue;
            }
        }

        /* AcceptEx on the completion context. The completion context will be 
         * signaled when a connection is accepted. 
         */
        if (!AcceptEx(nlsd, context->accept_socket,
                      context->buff,
                      0,
                      PADDED_ADDR_SIZE, 
                      PADDED_ADDR_SIZE,
                      &BytesRead,
                      &context->Overlapped)) {
            rv = apr_get_netos_error();
            if (rv == APR_FROM_OS_ERROR(WSAEINVAL)) {
                /* Hack alert. Occasionally, TransmitFile will not recycle the 
                 * accept socket (usually when the client disconnects early). 
                 * Get a new socket and try the call again.
                 */
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, ap_server_conf,
                       "winnt_accept: AcceptEx failed due to early client "
                       "disconnect. Reallocate the accept socket and try again.");
                continue;
            }
            else if (rv != APR_FROM_OS_ERROR(ERROR_IO_PENDING)) {
                ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                             "winnt_accept: AcceptEx failed. Attempting to recover.");
                closesocket(context->accept_socket);
                context->accept_socket = INVALID_SOCKET;
                Sleep(100);
                continue;
            }

            /* Wait for pending i/o. Wake up once per second to check for shutdown */
            while (1) {
                rv = WaitForSingleObject(context->Overlapped.hEvent, 1000);
                if (rv == WAIT_OBJECT_0) {
                    if (!GetOverlappedResult(context->Overlapped.hEvent, 
                                             &context->Overlapped, 
                                             &BytesRead, FALSE)) {
                        ap_log_error(APLOG_MARK,APLOG_WARNING, GetLastError(), ap_server_conf,
                                     "winnt_accept: Asynchronous AcceptEx failed.");
                        closesocket(context->accept_socket);
                        context->accept_socket = INVALID_SOCKET;
                    }
                    break;
                }
                /* WAIT_TIMEOUT */
                if (shutdown_in_progress) {
                    closesocket(context->accept_socket);
                    context->accept_socket = INVALID_SOCKET;
                    break;
                }
            }
            if (context->accept_socket == INVALID_SOCKET) {
                continue;
            }
        }

        /* Inherit the listen socket settings. Required for 
         * shutdown() to work 
         */
        if (setsockopt(context->accept_socket, SOL_SOCKET,
                       SO_UPDATE_ACCEPT_CONTEXT, (char *)&nlsd,
                       sizeof(nlsd))) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                         "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed.");
            /* Not a failure condition. Keep running. */
        }

        /* Get the local & remote address */
        GetAcceptExSockaddrs(context->buff,
                             0,
                             PADDED_ADDR_SIZE,
                             PADDED_ADDR_SIZE,
                             &context->sa_server,
                             &context->sa_server_len,
                             &context->sa_client,
                             &context->sa_client_len);

        sockinfo.os_sock = &context->accept_socket;
        sockinfo.local   = context->sa_server;
        sockinfo.remote  = context->sa_client;
        sockinfo.family  = APR_INET;
        sockinfo.type    = SOCK_STREAM;
        apr_os_sock_make(&context->sock, &sockinfo, context->ptrans);

        /* When a connection is received, send an io completion notification to
         * the ThreadDispatchIOCP. This function could be replaced by
         * mpm_post_completion_context(), but why do an extra function call...
         */
        PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, IOCP_CONNECTION_ACCEPTED,
                                   &context->Overlapped);
        context = NULL;
    }
    if (!shutdown_in_progress) {
        /* Yow, hit an irrecoverable error! Tell the child to die. */
        SetEvent(exit_event);
    }
    ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, ap_server_conf,
                 "Child %d: Accept thread exiting.", my_pid);
}
static PCOMP_CONTEXT winnt_get_connection(PCOMP_CONTEXT context)
{
    int rc;
    DWORD BytesRead;
    DWORD CompKey;
    LPOVERLAPPED pol;

    mpm_recycle_completion_context(context);

    apr_atomic_inc(&g_blocked_threads);
    while (1) {
        if (workers_may_exit) {
            apr_atomic_dec(&g_blocked_threads);
            return NULL;
        }
        rc = GetQueuedCompletionStatus(ThreadDispatchIOCP, &BytesRead, &CompKey,
                                       &pol, INFINITE);
        if (!rc) {
            rc = apr_get_os_error();
            ap_log_error(APLOG_MARK,APLOG_DEBUG, rc, ap_server_conf,
                             "Child %d: GetQueuedComplationStatus returned %d", my_pid, rc);
            continue;
        }

        switch (CompKey) {
        case IOCP_CONNECTION_ACCEPTED:
            context = CONTAINING_RECORD(pol, COMP_CONTEXT, Overlapped);
            break;
        case IOCP_SHUTDOWN:
            apr_atomic_dec(&g_blocked_threads);
            return NULL;
        default:
            apr_atomic_dec(&g_blocked_threads);
            return NULL;
        }
        break;
    }
    apr_atomic_dec(&g_blocked_threads);

    return context;
}

/*
 * worker_main()
 * Main entry point for the worker threads. Worker threads block in 
 * win*_get_connection() awaiting a connection to service.
 */
static void worker_main(long thread_num)
{
    static int requests_this_child = 0;
    PCOMP_CONTEXT context = NULL;
    ap_sb_handle_t *sbh;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf,
                 "Child %d: Worker thread %d starting.", my_pid, thread_num);
    while (1) {
        conn_rec *c;
        apr_int32_t disconnected;

        ap_update_child_status_from_indexes(0, thread_num, SERVER_READY, NULL);

        /* Grab a connection off the network */
        if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
            context = win9x_get_connection(context);
        }
        else {
            context = winnt_get_connection(context);
        }
        if (!context) {
            /* Time for the thread to exit */
            break;
        }

        /* Have we hit MaxRequestPerChild connections? */
        if (ap_max_requests_per_child) {
            requests_this_child++;
            if (requests_this_child > ap_max_requests_per_child) {
                SetEvent(max_requests_per_child_event);
            }
        }

        ap_create_sb_handle(&sbh, context->ptrans, 0, thread_num);
        c = ap_run_create_connection(context->ptrans, ap_server_conf,
                                     context->sock, thread_num, sbh,
                                     context->ba);

        if (c) {
            ap_process_connection(c, context->sock);
            apr_getsocketopt(context->sock, APR_SO_DISCONNECTED, &disconnected);
            if (!disconnected) {
                context->accept_socket = INVALID_SOCKET;
                ap_lingering_close(c);
            }
        }
        else {
            /* ap_run_create_connection closes the socket on failure */
            context->accept_socket = INVALID_SOCKET;
        }
    }

    ap_update_child_status_from_indexes(0, thread_num, SERVER_DEAD, 
                                        (request_rec *) NULL);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf,
                 "Child %d: Worker thread %d exiting.", my_pid, thread_num);
}

static void cleanup_thread(thread *handles, int *thread_cnt, int thread_to_clean)
{
    int i;

    CloseHandle(handles[thread_to_clean]);
    for (i = thread_to_clean; i < ((*thread_cnt) - 1); i++)
	handles[i] = handles[i + 1];
    (*thread_cnt)--;
}

/*
 * child_main() 
 * Entry point for the main control thread for the child process. 
 * This thread creates the accept thread, worker threads and
 * monitors the child process for maintenance and shutdown
 * events.
 */
static void create_listener_thread()
{
    int tid;
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        _beginthreadex(NULL, 0, (LPTHREAD_START_ROUTINE) win9x_accept,
                       NULL, 0, &tid);
    } else {
        /* Start an accept thread per listener 
         * XXX: Why would we have a NULL sd in our listeners?
         */
        ap_listen_rec *lr;
        for (lr = ap_listeners; lr; lr = lr->next) {
            if (lr->sd != NULL) {
                _beginthreadex(NULL, 1000, (LPTHREAD_START_ROUTINE) winnt_accept,
                               (void *) lr, 0, &tid);
            }
        }
    }
}
static void child_main()
{
    apr_status_t status;
    apr_hash_t *ht;
    ap_listen_rec *lr;
    HANDLE child_events[2];
    int threads_created = 0;
    int listener_started = 0;
    int tid;
    thread *child_handles;
    int rv;
    time_t end_time;
    int i;
    int cld;

    apr_pool_create(&pchild, pconf);
    apr_pool_tag(pchild, "pchild");

    ap_run_child_init(pchild, ap_server_conf);
    ht = apr_hash_make(pchild);

    /* Initialize the child_events */
    max_requests_per_child_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!max_requests_per_child_event) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Child %d: Failed to create a max_requests event.", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    child_events[0] = exit_event;
    child_events[1] = max_requests_per_child_event;

    allowed_globals.jobsemaphore = CreateSemaphore(NULL, 0, 1000000, NULL);
    apr_thread_mutex_create(&allowed_globals.jobmutex, 
                            APR_THREAD_MUTEX_DEFAULT, pchild);

    /*
     * Wait until we have permission to start accepting connections.
     * start_mutex is used to ensure that only one child ever
     * goes into the listen/accept loop at once.
     */
    status = apr_proc_mutex_lock(start_mutex);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_ERR, status, ap_server_conf,
                     "Child %d: Failed to acquire the start_mutex. Process will exit.", my_pid);
        exit(APEXIT_CHILDINIT);
    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Acquired the start mutex.", my_pid);

    /*
     * Create the worker thread dispatch IOCompletionPort
     * on Windows NT/2000
     */
    if (osver.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS) {
        /* Create the worker thread dispatch IOCP */
        ThreadDispatchIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,
                                                    NULL,
                                                    0,
                                                    0); /* CONCURRENT ACTIVE THREADS */
        apr_thread_mutex_create(&qlock, APR_THREAD_MUTEX_DEFAULT, pchild);
    }

    /* 
     * Create the pool of worker threads
     */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Starting %d worker threads.", my_pid, ap_threads_per_child);
    child_handles = (thread) apr_pcalloc(pchild, ap_threads_per_child * sizeof(int));
    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int *score_idx;
            int status = ap_scoreboard_image->servers[0][i].status;
            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
            }
            ap_update_child_status_from_indexes(0, i, SERVER_STARTING, NULL);
            child_handles[i] = (thread) _beginthreadex(NULL, 0, (LPTHREAD_START_ROUTINE) worker_main,
                                                       (void *) i, 0, &tid);
            if (child_handles[i] == 0) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                             "Child %d: _beginthreadex failed. Unable to create all worker threads. "
                             "Created %d of the %d threads requested with the ThreadsPerChild configuration directive.", 
                             threads_created, ap_threads_per_child);
                ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
                goto shutdown;
            }
            threads_created++;
            /* Save the score board index in ht keyed to the thread handle. We need this 
             * when cleaning up threads down below...
             */
            score_idx = apr_pcalloc(pchild, sizeof(int));
            *score_idx = i;
            apr_hash_set(ht, &child_handles[i], sizeof(thread), score_idx);
        }
        /* Start the listener only when workers are available */
        if (!listener_started && threads_created) {
            create_listener_thread();
            listener_started = 1;
        }
        if (threads_created == ap_threads_per_child) {
            break;
        }
        /* Check to see if the child has been told to exit */
        if (WaitForSingleObject(exit_event, 0) != WAIT_TIMEOUT) {
            break;
        }
        /* wait for previous generation to clean up an entry in the scoreboard */
        apr_sleep(1 * APR_USEC_PER_SEC);
    }

    /* Wait for one of three events:
     * exit_event: 
     *    The exit_event is signaled by the parent process to notify 
     *    the child that it is time to exit.
     *
     * max_requests_per_child_event: 
     *    This event is signaled by the worker threads to indicate that
     *    the process has handled MaxRequestsPerChild connections.
     *
     * TIMEOUT:
     *    To do periodic maintenance on the server (check for thread exits,
     *    number of completion contexts, etc.)
     */
    while (1) {
        rv = WaitForMultipleObjects(2, (HANDLE *) child_events, FALSE, 1000);
        cld = rv - WAIT_OBJECT_0;
        if (rv == WAIT_FAILED) {
            /* Something serious is wrong */
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                         "Child %d: WAIT_FAILED -- shutting down server");
            break;
        }
        else if (rv == WAIT_TIMEOUT) {
            apr_proc_other_child_check();
        }
        else if (cld == 0) {
            /* Exit event was signaled */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                         "Child %d: Exit event signaled. Child process is ending.", my_pid);
            break;
        }
        else {
            /* MaxRequestsPerChild event set by the worker threads.
             * Signal the parent to restart
             */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                         "Child %d: Process exiting because it reached "
                         "MaxRequestsPerChild. Signaling the parent to "
                         "restart a new child process.", my_pid);
            ap_signal_parent(SIGNAL_PARENT_RESTART);
            break;
        }
    }

    /* 
     * Time to shutdown the child process 
     */

 shutdown:
    /* Setting is_graceful will cause threads handling keep-alive connections 
     * to close the connection after handling the current request.
     */
    is_graceful = 1;

    /* Close the listening sockets. Note, we must close the listeners
     * before closing any accept sockets pending in AcceptEx to prevent
     * memory leaks in the kernel.
     */
    for (lr = ap_listeners; lr ; lr = lr->next) {
        apr_socket_close(lr->sd);
    }

    /* Shutdown listener threads and pending AcceptEx socksts 
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
        ap_log_error(APLOG_MARK,APLOG_NOTICE, rv, ap_server_conf, 
                     "Child %d: Released the start mutex", my_pid);
    }
    else {
        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf, 
                     "Child %d: Failure releasing the start mutex", my_pid);
    }

    /* Shutdown the worker threads */
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        for (i = 0; i < threads_created; i++) {
            add_job(-1);
        }
    }
    else { /* Windows NT/2000 */
        /* Post worker threads blocked on the ThreadDispatch IOCompletion port */
        while (g_blocked_threads > 0) {
            ap_log_error(APLOG_MARK,APLOG_INFO, APR_SUCCESS, ap_server_conf, 
                         "Child %d: %d threads blocked on the completion port", my_pid, g_blocked_threads);
            for (i=g_blocked_threads; i > 0; i--) {
                PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, IOCP_SHUTDOWN, NULL);
            }
            Sleep(1000);
        }
        /* Empty the accept queue of completion contexts */
        apr_thread_mutex_lock(qlock);
        while (qhead) {
            CloseHandle(qhead->Overlapped.hEvent);
            closesocket(qhead->accept_socket);
            qhead = qhead->next;
        }
        apr_thread_mutex_unlock(qlock);
    }

    /* Give busy worker threads a chance to service their connections */
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: Waiting for %d worker threads to exit.", my_pid, threads_created);
    end_time = time(NULL) + 180;
    while (threads_created) {
        rv = wait_for_many_objects(threads_created, child_handles, end_time - time(NULL));
        if (rv != WAIT_TIMEOUT) {
            rv = rv - WAIT_OBJECT_0;
            ap_assert((rv >= 0) && (rv < threads_created));
            cleanup_thread(child_handles, &threads_created, rv);
            continue;
        }
        break;
    }

    /* Kill remaining threads off the hard way */
    if (threads_created) {
        ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                     "Child %d: Terminating %d threads that failed to exit.", my_pid);
    }
    for (i = 0; i < threads_created; i++) {
        int *score_idx;
        TerminateThread(child_handles[i], 1);
        CloseHandle(child_handles[i]);
        /* Reset the scoreboard entry for the thread we just whacked */
        score_idx = apr_hash_get(ht, &child_handles[i], sizeof(thread));
        ap_update_child_status_from_indexes(0, *score_idx, SERVER_DEAD, NULL);        
    }
    ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, 
                 "Child %d: All worker threads have exited.", my_pid);

    CloseHandle(allowed_globals.jobsemaphore);
    apr_thread_mutex_destroy(allowed_globals.jobmutex);
    if (osver.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
    	apr_thread_mutex_destroy(qlock);

    apr_pool_destroy(pchild);
    CloseHandle(exit_event);
}

static int send_handles_to_child(apr_pool_t *p, HANDLE child_exit_event, HANDLE hProcess, HANDLE hPipeWrite)
{
    apr_status_t rv;
    HANDLE hScore;
    HANDLE hDup;
    HANDLE hCurrentProcess = GetCurrentProcess();
    DWORD BytesWritten;

    if (!DuplicateHandle(hCurrentProcess, child_exit_event, hProcess, &hDup,
                         EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Unable to duplicate the exit event handle for the child");
        return -1;
    }
    if (!WriteFile(hPipeWrite, &hDup, sizeof(hDup),
                   &BytesWritten, (LPOVERLAPPED) NULL)
            || (BytesWritten != sizeof(hDup))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Unable to send the exit event handle to the child");
        return -1;
    }

    if ((rv = apr_os_shm_get(&hScore, ap_scoreboard_shm)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                     "Parent: Unable to retrieve the scoreboard handle for the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, hScore, hProcess, &hDup,
                         FILE_MAP_READ | FILE_MAP_WRITE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Unable to duplicate the scoreboard handle to the child");
        return -1;
    }
    if (!WriteFile(hPipeWrite, &hDup, sizeof(hDup),
                   &BytesWritten, (LPOVERLAPPED) NULL)
            || (BytesWritten != sizeof(hDup))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf,
                     "Parent: Unable to send the scoreboard handle to the child");
        return -1;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                 "Parent: Sent the scoreboard to the child");
    return 0;
}

static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId, HANDLE hPipeWrite)
{
    int lcnt = 0;
    ap_listen_rec *lr;
    LPWSAPROTOCOL_INFO  lpWSAProtocolInfo;
    DWORD BytesWritten;

    /* Run the chain of open sockets. For each socket, duplicate it 

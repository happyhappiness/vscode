        }
    }

    return context;
}

apr_status_t mpm_post_completion_context(PCOMP_CONTEXT context,
                                         io_state_e state)
{
    LPOVERLAPPED pOverlapped;
    if (context)
        pOverlapped = &context->Overlapped;
    else
        pOverlapped = NULL;

    PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, state, pOverlapped);
    return APR_SUCCESS;
}


/*
 * find_ready_listener()
 * Only used by Win9* and should go away when the win9*_accept() function is
 * reimplemented using apr_poll().
 */
static ap_listen_rec *head_listener;

static APR_INLINE ap_listen_rec *find_ready_listener(fd_set * main_fds)
{
    ap_listen_rec *lr;
    SOCKET nsd;

    lr = head_listener;
    do {
        apr_os_sock_get(&nsd, lr->sd);
        if (FD_ISSET(nsd, main_fds)) {
            head_listener = lr->next;
            if (!head_listener) {
                head_listener = ap_listeners;
            }
            return lr;
        }
        lr = lr->next;
        if (!lr) {
            lr = ap_listeners;
        }
    } while (lr != head_listener);
    return NULL;
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
    SOCKET sock;
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


static void add_job(SOCKET sock)
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


static SOCKET remove_job(void)
{
    joblist *job;
    SOCKET sock;

    WaitForSingleObject(allowed_globals.jobsemaphore, INFINITE);
    apr_thread_mutex_lock(allowed_globals.jobmutex);

    if (shutdown_in_progress && !allowed_globals.jobhead) {
        apr_thread_mutex_unlock(allowed_globals.jobmutex);
        return (INVALID_SOCKET);
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


static unsigned int __stdcall win9x_accept(void * dummy)
{
    struct timeval tv;
    fd_set main_fds;
    int wait_time = 1;
    SOCKET csd;
    SOCKET nsd = INVALID_SOCKET;
    int count_select_errors = 0;
    int rc;
    int clen;
    ap_listen_rec *lr;
    struct fd_set listenfds;
#if APR_HAVE_IPV6
    struct sockaddr_in6 sa_client;
#else
    struct sockaddr_in sa_client;
#endif

    /* Setup the listeners
     * ToDo: Use apr_poll()
     */
    FD_ZERO(&listenfds);
    for (lr = ap_listeners; lr; lr = lr->next) {
        if (lr->sd != NULL) {
            apr_os_sock_get(&nsd, lr->sd);
            FD_SET(nsd, &listenfds);
            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                         "Child %lu: Listening on port %d.", my_pid, lr->bind_addr->port);
        }
    }

    head_listener = ap_listeners;

    while (!shutdown_in_progress) {
        tv.tv_sec = wait_time;
        tv.tv_usec = 0;
        memcpy(&main_fds, &listenfds, sizeof(fd_set));

        /* First parameter of select() is ignored on Windows */
        rc = select(0, &main_fds, NULL, NULL, &tv);

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
        } while (csd == INVALID_SOCKET && APR_STATUS_IS_EINTR(apr_get_netos_error()));

        if (csd == INVALID_SOCKET) {
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
    return 0;
}


static PCOMP_CONTEXT win9x_get_connection(PCOMP_CONTEXT context)
{
    apr_os_sock_info_t sockinfo;
    int len, salen;
#if APR_HAVE_IPV6
    salen = sizeof(struct sockaddr_in6);
#else
    salen = sizeof(struct sockaddr_in);
#endif


    if (context == NULL) {
        /* allocate the completion context and the transaction pool */
        apr_allocator_t *allocator;
        apr_thread_mutex_lock(child_lock);
        context = apr_pcalloc(pchild, sizeof(COMP_CONTEXT));
        apr_allocator_create(&allocator);
        apr_allocator_max_free_set(allocator, ap_max_mem_free);
        apr_pool_create_ex(&context->ptrans, pchild, NULL, allocator);
        apr_allocator_owner_set(allocator, context->ptrans);
        apr_pool_tag(context->ptrans, "transaction");
        apr_thread_mutex_unlock(child_lock);
    }

    while (1) {
        apr_pool_clear(context->ptrans);
        context->ba = apr_bucket_alloc_create(context->ptrans);
        context->accept_socket = remove_job();
        if (context->accept_socket == INVALID_SOCKET) {
            return NULL;
        }
        len = salen;
        context->sa_server = apr_palloc(context->ptrans, len);
        if (getsockname(context->accept_socket,
                        context->sa_server, &len)== SOCKET_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                         "getsockname failed");
            continue;
        }
        len = salen;
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
        sockinfo.family  = context->sa_server->sa_family;
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

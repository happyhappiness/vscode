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
        context->ba = apr_bucket_alloc_create(pchild);
        apr_thread_mutex_unlock(child_lock);
    }

    while (1) {
        apr_pool_clear(context->ptrans);
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
 *
 * winnt_accept()
 *    One or more accept threads run in this function, each of which accepts
 *    connections off the network and calls PostQueuedCompletionStatus() to
 *    queue an io completion packet to the ThreadDispatch IOCompletionPort.
 * winnt_get_connection()
 *    Worker threads block on the ThreadDispatch IOCompletionPort awaiting
 *    connections to service.
 */
#define MAX_ACCEPTEX_ERR_COUNT 100
static unsigned int __stdcall winnt_accept(void *lr_)
{
    ap_listen_rec *lr = (ap_listen_rec *)lr_;
    apr_os_sock_info_t sockinfo;
    PCOMP_CONTEXT context = NULL;
    DWORD BytesRead;
    SOCKET nlsd;
    int rv, err_count = 0;
#if APR_HAVE_IPV6
    SOCKADDR_STORAGE ss_listen;
    int namelen = sizeof(ss_listen);
#endif

    apr_os_sock_get(&nlsd, lr->sd);

#if APR_HAVE_IPV6
    if (getsockname(nlsd, (struct sockaddr *)&ss_listen, &namelen) == SOCKET_ERROR) {
        ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_netos_error(), ap_server_conf,
                    "winnt_accept: getsockname error on listening socket, is IPv6 available?");
        return 1;
   }
#endif

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                 "Child %d: Starting thread to listen on port %d.", my_pid, lr->bind_addr->port);
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
#if APR_HAVE_IPV6
        if (context->accept_socket == INVALID_SOCKET) {
            context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM, IPPROTO_TCP);
            context->socket_family = ss_listen.ss_family;
        }
        else if (context->socket_family != ss_listen.ss_family) {
            closesocket(context->accept_socket);
            context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM, IPPROTO_TCP);
            context->socket_family = ss_listen.ss_family;
        }

        if (context->accept_socket == INVALID_SOCKET) {
            ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                         "winnt_accept: Failed to allocate an accept socket. "
                         "Temporary resource constraint? Try again.");
            Sleep(100);
            continue;
        }
#else
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
#endif
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
            if ((rv == APR_FROM_OS_ERROR(WSAEINVAL)) ||
                (rv == APR_FROM_OS_ERROR(WSAENOTSOCK))) {

  *    connections off the network and calls PostQueuedCompletionStatus() to
  *    queue an io completion packet to the ThreadDispatch IOCompletionPort.
  * winnt_get_connection()
  *    Worker threads block on the ThreadDispatch IOCompletionPort awaiting
  *    connections to service.
  */
-#define MAX_ACCEPTEX_ERR_COUNT 100
+#define MAX_ACCEPTEX_ERR_COUNT 10
+
 static unsigned int __stdcall winnt_accept(void *lr_)
 {
     ap_listen_rec *lr = (ap_listen_rec *)lr_;
     apr_os_sock_info_t sockinfo;
-    PCOMP_CONTEXT context = NULL;
+    winnt_conn_ctx_t *context = NULL;
     DWORD BytesRead;
     SOCKET nlsd;
-    int rv, err_count = 0;
+    core_server_config *core_sconf;
+    const char *accf_name;
+    int rv;
+    int accf;
+    int err_count = 0;
+    HANDLE events[3];
 #if APR_HAVE_IPV6
     SOCKADDR_STORAGE ss_listen;
     int namelen = sizeof(ss_listen);
 #endif
+    u_long zero = 0;
+
+    core_sconf = ap_get_module_config(ap_server_conf->module_config,
+                                      &core_module);
+    accf_name = apr_table_get(core_sconf->accf_map, lr->protocol);
+
+    if (strcmp(accf_name, "data") == 0)
+        accf = 2;
+    else if (strcmp(accf_name, "connect") == 0)
+        accf = 1;
+    else if (strcmp(accf_name, "none") == 0)
+        accf = 0;
+    else {
+        accf = 0;
+        accf_name = "none";
+        ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), 
+                     ap_server_conf,
+                     "winnt_accept: unrecognized AcceptFilter '%s', "
+                     "only 'data', 'connect' or 'none' are valid. "
+                     "Using 'none' instead", accf_name);
+    }
 
     apr_os_sock_get(&nlsd, lr->sd);
 
 #if APR_HAVE_IPV6
     if (getsockname(nlsd, (struct sockaddr *)&ss_listen, &namelen) == SOCKET_ERROR) {
-        ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_netos_error(), ap_server_conf,
-                    "winnt_accept: getsockname error on listening socket, is IPv6 available?");
+        ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_netos_error(), 
+                     ap_server_conf,
+                     "winnt_accept: getsockname error on listening socket, "
+                     "is IPv6 available?");
         return 1;
    }
 #endif
 
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
-                 "Child %lu: Starting thread to listen on port %d.", my_pid, lr->bind_addr->port);
+    if (accf > 0) /* 'data' or 'connect' */
+    {
+        /* first, high priority event is an already accepted connection */
+        events[1] = exit_event;
+        events[2] = max_requests_per_child_event;
+    }
+    else /* accf == 0, 'none' */
+    {
+reinit: /* target of data or connect upon too many AcceptEx failures */
+
+        /* last, low priority event is a not yet accepted connection */
+        events[0] = exit_event;
+        events[1] = max_requests_per_child_event;
+        events[2] = CreateEvent(NULL, FALSE, FALSE, NULL);
+
+        /* The event needs to be removed from the accepted socket,
+         * if not removed from the listen socket prior to accept(),
+         */
+        rv = WSAEventSelect(nlsd, events[2], FD_ACCEPT);
+        if (rv) {
+            ap_log_error(APLOG_MARK, APLOG_ERR,
+                         apr_get_netos_error(), ap_server_conf,
+                         "WSAEventSelect() failed.");
+            CloseHandle(events[2]);
+            return 1;
+        }
+    }
+
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf,
+                 "Child %d: Accept thread listening on %s:%d using %s", my_pid,
+                 lr->bind_addr->hostname ? lr->bind_addr->hostname : "*",
+                 lr->bind_addr->port, accf_name);
+
     while (!shutdown_in_progress) {
         if (!context) {
             context = mpm_get_completion_context();
             if (!context) {
+                /* Hopefully a temporary condition in the provider? */
+                ++err_count;
+                if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
+                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                                 "winnt_accept: Too many failures grabbing a "
+                                 "connection ctx.  Aborting.");
+                    break;
+                }
+
                 /* Temporary resource constraint? */
-                Sleep(0);
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, apr_get_netos_error(), 
+                             ap_server_conf,
+                             "winnt_accept: Failed to grab a connection ctx."
+                             "  Temporary resource constraint? Retrying.");
+                Sleep(100);
                 continue;
             }
         }
 
-        /* Create and initialize the accept socket */
-#if APR_HAVE_IPV6
-        if (context->accept_socket == INVALID_SOCKET) {
-            context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM, IPPROTO_TCP);
-            context->socket_family = ss_listen.ss_family;
-        }
-        else if (context->socket_family != ss_listen.ss_family) {
-            closesocket(context->accept_socket);
-            context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM, IPPROTO_TCP);
-            context->socket_family = ss_listen.ss_family;
-        }
+        if (accf > 0) /* Either 'connect' or 'data' */
+        {
+            DWORD len;
+            char *buf;
 
-        if (context->accept_socket == INVALID_SOCKET) {
-            ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
-                         "winnt_accept: Failed to allocate an accept socket. "
-                         "Temporary resource constraint? Try again.");
-            Sleep(100);
-            continue;
-        }
+            /* Create and initialize the accept socket */
+#if APR_HAVE_IPV6
+            if (context->accept_socket == INVALID_SOCKET) {
+                context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM, 
+                                                IPPROTO_TCP);
+                context->socket_family = ss_listen.ss_family;
+            }
+            else if (context->socket_family != ss_listen.ss_family) {
+                closesocket(context->accept_socket);
+                context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM, 
+                                                IPPROTO_TCP);
+                context->socket_family = ss_listen.ss_family;
+            }
 #else
-        if (context->accept_socket == INVALID_SOCKET) {
-            context->accept_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
+            if (context->accept_socket == INVALID_SOCKET)
+                context->accept_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
+#endif
+
             if (context->accept_socket == INVALID_SOCKET) {
-                /* Another temporary condition? */
-                ap_log_error(APLOG_MARK,APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
+                ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), 
+                             ap_server_conf,
                              "winnt_accept: Failed to allocate an accept socket. "
                              "Temporary resource constraint? Try again.");
                 Sleep(100);
                 continue;
             }
-        }
-#endif
-        /* AcceptEx on the completion context. The completion context will be
-         * signaled when a connection is accepted.
-         */
-        if (!AcceptEx(nlsd, context->accept_socket,
-                      context->buff,
-                      0,
-                      PADDED_ADDR_SIZE,
-                      PADDED_ADDR_SIZE,
-                      &BytesRead,
-                      &context->Overlapped)) {
-            rv = apr_get_netos_error();
-            if ((rv == APR_FROM_OS_ERROR(WSAEINVAL)) ||
-                (rv == APR_FROM_OS_ERROR(WSAENOTSOCK))) {
-                /* We can get here when:
-                 * 1) the client disconnects early
-                 * 2) TransmitFile does not properly recycle the accept socket (typically
-                 *    because the client disconnected)
-                 * 3) there is VPN or Firewall software installed with buggy AcceptEx implementation
-                 * 4) the webserver is using a dynamic address that has changed
-                 */
-                ++err_count;
-                closesocket(context->accept_socket);
-                context->accept_socket = INVALID_SOCKET;
-                if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
-                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
-                                 "Child %lu: Encountered too many errors accepting client connections. "
-                                 "Possible causes: dynamic address renewal, or incompatible VPN or firewall software. "
-                                 "Try using the Win32DisableAcceptEx directive.", my_pid);
-                    err_count = 0;
-                }
-                continue;
+
+            if (accf == 2) { /* 'data' */
+                len = APR_BUCKET_BUFF_SIZE;
+                buf = apr_bucket_alloc(len, context->ba); /* XXX: check for failure? */
+                len -= PADDED_ADDR_SIZE * 2;
             }
-            else if ((rv != APR_FROM_OS_ERROR(ERROR_IO_PENDING)) &&
-                     (rv != APR_FROM_OS_ERROR(WSA_IO_PENDING))) {
-                ++err_count;
-                if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
-                    ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
-                                 "Child %lu: Encountered too many errors accepting client connections. "
-                                 "Possible causes: Unknown. "
-                                 "Try using the Win32DisableAcceptEx directive.", my_pid);
-                    err_count = 0;
-                }
-                closesocket(context->accept_socket);
-                context->accept_socket = INVALID_SOCKET;
-                continue;
+            else {
+                len = 0;
+                buf = context->buff;
             }
-            err_count = 0;
 
-            /* Wait for pending i/o.
-             * Wake up once per second to check for shutdown .
-             * XXX: We should be waiting on exit_event instead of polling
+            /* AcceptEx on the completion context. The completion context will be
+             * signaled when a connection is accepted.
              */
-            while (1) {
-                rv = WaitForSingleObject(context->Overlapped.hEvent, 1000);
-                if (rv == WAIT_OBJECT_0) {
-                    if (context->accept_socket == INVALID_SOCKET) {
-                        /* socket already closed */
-                        break;
+            if (!AcceptEx(nlsd, context->accept_socket, buf, len,
+                          PADDED_ADDR_SIZE, PADDED_ADDR_SIZE, &BytesRead,
+                          &context->overlapped)) {
+                rv = apr_get_netos_error();
+                if ((rv == APR_FROM_OS_ERROR(WSAECONNRESET)) ||
+                    (rv == APR_FROM_OS_ERROR(WSAEACCES))) {
+                    /* We can get here when:
+                     * 1) the client disconnects early
+                     * 2) handshake was incomplete
+                     */
+                    if (accf == 2)
+                        apr_bucket_free(buf);
+                    closesocket(context->accept_socket);
+                    context->accept_socket = INVALID_SOCKET;
+                    continue;
+                }
+                else if ((rv == APR_FROM_OS_ERROR(WSAEINVAL)) ||
+                         (rv == APR_FROM_OS_ERROR(WSAENOTSOCK))) {
+                    /* We can get here when:
+                     * 1) TransmitFile does not properly recycle the accept socket (typically
+                     *    because the client disconnected)
+                     * 2) there is VPN or Firewall software installed with 
+                     *    buggy WSAAccept or WSADuplicateSocket implementation
+                     * 3) the dynamic address / adapter has changed
+                     * Give five chances, then fall back on AcceptFilter 'none'
+                     */
+                    if (accf == 2)
+                        apr_bucket_free(buf);
+                    closesocket(context->accept_socket);
+                    context->accept_socket = INVALID_SOCKET;
+                    ++err_count;
+                    if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
+                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                                     "Child %d: Encountered too many AcceptEx "
+                                     "faults accepting client connections. "
+                                     "Possible causes: dynamic address renewal, "
+                                     "or incompatible VPN or firewall software. ",
+                                     my_pid);
+                        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
+                                     "winnt_mpm: falling back to "
+                                     "'AcceptFilter none'.");
+                        err_count = 0;
+                        accf = 0;
                     }
-                    if (!GetOverlappedResult((HANDLE)context->accept_socket,
-                                             &context->Overlapped,
+                    continue;
+                }
+                else if ((rv != APR_FROM_OS_ERROR(ERROR_IO_PENDING)) &&
+                         (rv != APR_FROM_OS_ERROR(WSA_IO_PENDING))) {
+                    if (accf == 2)
+                        apr_bucket_free(buf);
+                    closesocket(context->accept_socket);
+                    context->accept_socket = INVALID_SOCKET;
+                    ++err_count;
+                    if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
+                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                                     "Child %d: Encountered too many AcceptEx "
+                                     "faults accepting client connections.",
+                                     my_pid);
+                        ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, ap_server_conf,
+                                     "winnt_mpm: falling back to "
+                                     "'AcceptFilter none'.");
+                        err_count = 0;
+                        accf = 0;
+                        goto reinit;
+                    }
+                    continue;
+                }
+
+                err_count = 0;
+                events[0] = context->overlapped.hEvent;
+
+                do {
+                    rv = WaitForMultipleObjectsEx(3, events, FALSE, INFINITE, TRUE);
+                } while (rv == WAIT_IO_COMPLETION);
+
+                if (rv == WAIT_OBJECT_0) {
+                    if ((context->accept_socket != INVALID_SOCKET) &&
+                        !GetOverlappedResult((HANDLE)context->accept_socket,
+                                             &context->overlapped,
                                              &BytesRead, FALSE)) {
                         ap_log_error(APLOG_MARK, APLOG_WARNING,
                                      apr_get_os_error(), ap_server_conf,
                              "winnt_accept: Asynchronous AcceptEx failed.");
                         closesocket(context->accept_socket);
                         context->accept_socket = INVALID_SOCKET;
                     }
-                    break;
                 }
-                /* WAIT_TIMEOUT */
-                if (shutdown_in_progress) {
+                else {
+                    /* exit_event triggered or event handle was closed */
                     closesocket(context->accept_socket);
                     context->accept_socket = INVALID_SOCKET;
+                    if (accf == 2)
+                        apr_bucket_free(buf);
                     break;
                 }
+
+                if (context->accept_socket == INVALID_SOCKET) {
+                    if (accf == 2)
+                        apr_bucket_free(buf);
+                    continue;
+                }
+            }
+            err_count = 0;
+
+            /* Potential optimization; consider handing off to the worker */
+
+            /* Inherit the listen socket settings. Required for
+             * shutdown() to work
+             */
+            if (setsockopt(context->accept_socket, SOL_SOCKET,
+                           SO_UPDATE_ACCEPT_CONTEXT, (char *)&nlsd,
+                           sizeof(nlsd))) {
+                ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(),
+                             ap_server_conf,
+                             "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed.");
+                /* Not a failure condition. Keep running. */
+            }
+
+            /* Get the local & remote address 
+             * TODO; error check
+             */
+            GetAcceptExSockaddrs(buf, len, PADDED_ADDR_SIZE, PADDED_ADDR_SIZE,
+                                 &context->sa_server, &context->sa_server_len,
+                                 &context->sa_client, &context->sa_client_len);
+
+            /* For 'data', craft a bucket for our data result 
+             * and pass to worker_main as context->overlapped.Pointer
+             */
+            if (accf == 2 && BytesRead)
+            {
+                apr_bucket *b;
+                b = apr_bucket_heap_create(buf, APR_BUCKET_BUFF_SIZE,
+                                           apr_bucket_free, context->ba);
+                /* Adjust the bucket to refer to the actual bytes read */
+                b->length = BytesRead;
+                context->overlapped.Pointer = b;
+            }
+            else
+                context->overlapped.Pointer = NULL;
+        }
+        else /* (accf = 0)  e.g. 'none' */
+        {
+            /* There is no socket reuse without AcceptEx() */
+            if (context->accept_socket != INVALID_SOCKET)
+                closesocket(context->accept_socket);
+
+            /* This could be a persistant event per-listener rather than
+             * per-accept.  However, the event needs to be removed from
+             * the target socket if not removed from the listen socket
+             * prior to accept(), or the event select is inherited.
+             * and must be removed from the accepted socket.
+             */
+
+            do {
+                rv = WaitForMultipleObjectsEx(3, events, FALSE, INFINITE, TRUE);
+            } while (rv == WAIT_IO_COMPLETION);
+
+
+            if (rv != WAIT_OBJECT_0 + 2) {
+                /* not FD_ACCEPT; 
+                 * exit_event triggered or event handle was closed 
+                 */
+                break;
             }
+
+            context->sa_client = NULL;
+            context->sa_server = (void *) context->buff;
+            context->sa_server_len = sizeof(context->buff);
+            context->accept_socket = accept(nlsd, context->sa_server,
+                                            &context->sa_server_len);
+
             if (context->accept_socket == INVALID_SOCKET) {
-                continue;
+
+                rv = apr_get_netos_error();
+                if (   rv == APR_FROM_OS_ERROR(WSAECONNRESET)
+                    || rv == APR_FROM_OS_ERROR(WSAEINPROGRESS)
+                    || rv == APR_FROM_OS_ERROR(WSAEWOULDBLOCK) ) {
+                    ap_log_error(APLOG_MARK, APLOG_DEBUG,
+                                 rv, ap_server_conf,
+                                 "accept() failed, retrying.");
+                    continue;
+                }
+
+                /* A more serious error that 'retry', log it */
+                ap_log_error(APLOG_MARK, APLOG_WARNING,
+                             rv, ap_server_conf,
+                             "accept() failed.");
+
+                if (   rv == APR_FROM_OS_ERROR(WSAEMFILE)
+                    || rv == APR_FROM_OS_ERROR(WSAENOBUFS) ) {
+                    /* Hopefully a temporary condition in the provider? */
+                    Sleep(100);
+                    ++err_count;
+                    if (err_count > MAX_ACCEPTEX_ERR_COUNT) {
+                        ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
+                                     "Child %d: Encountered too many accept() "
+                                     "resource faults, aborting.",
+                                     my_pid);
+                        break;
+                    }
+                    continue;
+                }
+                break;
             }
+            /* Per MSDN, cancel the inherited association of this socket 
+             * to the WSAEventSelect API, and restore the state corresponding
+             * to apr_os_sock_make's default assumptions (really, a flaw within
+             * os_sock_make and os_sock_put that it does not query).
+             */
+            WSAEventSelect(context->accept_socket, 0, 0);
+            context->overlapped.Pointer = NULL;
+            err_count = 0;
         }
-        err_count = 0;
-        /* Inherit the listen socket settings. Required for
-         * shutdown() to work
-         */
-        if (setsockopt(context->accept_socket, SOL_SOCKET,
-                       SO_UPDATE_ACCEPT_CONTEXT, (char *)&nlsd,
-                       sizeof(nlsd))) {
-            ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
-                         "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed.");
-            /* Not a failure condition. Keep running. */
-        }
-
-        /* Get the local & remote address */
-        GetAcceptExSockaddrs(context->buff,
-                             0,
-                             PADDED_ADDR_SIZE,
-                             PADDED_ADDR_SIZE,
-                             &context->sa_server,
-                             &context->sa_server_len,
-                             &context->sa_client,
-                             &context->sa_client_len);
 
         sockinfo.os_sock = &context->accept_socket;
         sockinfo.local   = context->sa_server;
         sockinfo.remote  = context->sa_client;
         sockinfo.family  = context->sa_server->sa_family;
         sockinfo.type    = SOCK_STREAM;
+        /* Restore the state corresponding to apr_os_sock_make's default
+         * assumption of timeout -1 (really, a flaw of os_sock_make and 
+         * os_sock_put that it does not query to determine ->timeout).
+         * XXX: Upon a fix to APR, these three statements should disappear.
+         */
+        ioctlsocket(context->accept_socket, FIONBIO, &zero);
+        setsockopt(context->accept_socket, SOL_SOCKET, SO_RCVTIMEO, 
+                   (char *) &zero, sizeof(zero));
+        setsockopt(context->accept_socket, SOL_SOCKET, SO_SNDTIMEO, 
+                   (char *) &zero, sizeof(zero));
         apr_os_sock_make(&context->sock, &sockinfo, context->ptrans);
 
-        /* When a connection is received, send an io completion notification to
-         * the ThreadDispatchIOCP. This function could be replaced by
-         * mpm_post_completion_context(), but why do an extra function call...
+        /* When a connection is received, send an io completion notification
+         * to the ThreadDispatchIOCP.
          */
-        PostQueuedCompletionStatus(ThreadDispatchIOCP, 0, IOCP_CONNECTION_ACCEPTED,
-                                   &context->Overlapped);
+        PostQueuedCompletionStatus(ThreadDispatchIOCP, BytesRead,
+                                   IOCP_CONNECTION_ACCEPTED,
+                                   &context->overlapped);
         context = NULL;
     }
+    if (!accf)
+        CloseHandle(events[2]);
+
     if (!shutdown_in_progress) {
         /* Yow, hit an irrecoverable error! Tell the child to die. */
         SetEvent(exit_event);
     }
+
     ap_log_error(APLOG_MARK, APLOG_INFO, APR_SUCCESS, ap_server_conf,
-                 "Child %lu: Accept thread exiting.", my_pid);
+                 "Child %d: Accept thread exiting.", my_pid);
     return 0;
 }
 
 
-static PCOMP_CONTEXT winnt_get_connection(PCOMP_CONTEXT context)
+static winnt_conn_ctx_t *winnt_get_connection(winnt_conn_ctx_t *context)
 {
     int rc;
     DWORD BytesRead;
     LPOVERLAPPED pol;
 #ifdef _WIN64
     ULONG_PTR CompKey;

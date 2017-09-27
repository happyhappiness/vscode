            DWORD len;
            char *buf;

            /* Create and initialize the accept socket */
#if APR_HAVE_IPV6
            if (context->accept_socket == INVALID_SOCKET) {
                context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM,
                                                IPPROTO_TCP);
                context->socket_family = ss_listen.ss_family;
            }
            else if (context->socket_family != ss_listen.ss_family) {
                closesocket(context->accept_socket);
                context->accept_socket = socket(ss_listen.ss_family, SOCK_STREAM,
                                                IPPROTO_TCP);
                context->socket_family = ss_listen.ss_family;
            }
#else
            if (context->accept_socket == INVALID_SOCKET)
                context->accept_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif

            if (context->accept_socket == INVALID_SOCKET) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(),
                             ap_server_conf, APLOGNO(00336)
                             "winnt_accept: Failed to allocate an accept socket. "
                             "Temporary resource constraint? Try again.");
                Sleep(100);
                continue;
            }

            if (accf == 2) { /* 'data' */
                len = APR_BUCKET_BUFF_SIZE;
                buf = apr_bucket_alloc(len, context->ba);
                len -= PADDED_ADDR_SIZE * 2;
            }
            else /* (accf == 1) 'connect' */ {
                len = 0;
                buf = context->buff;
            }

            /* AcceptEx on the completion context. The completion context will be
             * signaled when a connection is accepted.

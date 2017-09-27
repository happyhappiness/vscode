                ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf, APLOGNO(00347)
                             "getpeername failed");
                memset(&context->sa_client, '\0', sizeof(context->sa_client));
            }
        }

        sockinfo.os_sock = &context->accept_socket;
        sockinfo.local   = context->sa_server;
        sockinfo.remote  = context->sa_client;
        sockinfo.family  = context->sa_server->sa_family;
        sockinfo.type    = SOCK_STREAM;
        /* Restore the state corresponding to apr_os_sock_make's default
         * assumption of timeout -1 (really, a flaw of os_sock_make and
         * os_sock_put that it does not query to determine ->timeout).
         * XXX: Upon a fix to APR, these three statements should disappear.
         */
        ioctlsocket(context->accept_socket, FIONBIO, &zero);

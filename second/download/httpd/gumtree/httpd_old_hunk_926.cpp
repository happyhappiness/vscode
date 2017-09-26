                }
            }
            if (context->accept_socket == INVALID_SOCKET) {
                continue;
            }
        }

        err_count = 0;
        /* Inherit the listen socket settings. Required for 
         * shutdown() to work 
         */
        if (setsockopt(context->accept_socket, SOL_SOCKET,
                       SO_UPDATE_ACCEPT_CONTEXT, (char *)&nlsd,
                       sizeof(nlsd))) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), ap_server_conf,
                         "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed.");

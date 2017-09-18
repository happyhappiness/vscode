            /* Check the listen queue on all sockets for requests */
            memcpy(&main_fds, &listenfds, sizeof(fd_set));
            srv = select(listenmaxfd + 1, &main_fds, NULL, NULL, &tv);

            if (srv <= 0) {
                if (srv < 0) {
                    ap_log_error(APLOG_MARK, APLOG_NOTICE, WSAGetLastError(), ap_server_conf,
                        "select() failed on listen socket");
                    apr_thread_yield();
                }
                continue;
            }


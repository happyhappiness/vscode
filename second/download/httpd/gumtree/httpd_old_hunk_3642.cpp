                             proxy_function,
                             worker->s->hostname);
                break;
            }
            conn->connection = NULL;

            sa.sun_family = AF_UNIX;
            apr_cpystrn(sa.sun_path, conn->uds_path, sizeof(sa.sun_path));

            rv = socket_connect_un(newsock, &sa);
            if (rv != APR_SUCCESS) {
                apr_socket_close(newsock);
                ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02454)
                             "%s: attempt to connect to Unix domain socket "
                             "%s (%s) failed",
                             proxy_function,
                             conn->uds_path,
                             worker->s->hostname);
                break;
            }
        }
        else
#endif
        {
            if ((rv = apr_socket_create(&newsock, backend_addr->family,
                                        SOCK_STREAM, APR_PROTO_TCP,

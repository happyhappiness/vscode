int main(int argc, const char * const argv[])
{
    apr_file_t *infd, *skwrapper;
    apr_sockaddr_t *skaddr;
    apr_getopt_t *gopt;
    apr_socket_t *skt;
    apr_pool_t *pool;
    apr_status_t rv;
    apr_proc_t proc;


    /* Command line arguments */
    int num_to_start = 1, port = 0;
    const char *interface = NULL;
    const char *command = NULL;

    apr_app_initialize(&argc, &argv, NULL);

    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);

    rv = apr_getopt_init(&gopt, pool, argc, argv);
    if (rv) {
        return EXIT_FAILURE;
    }

    for (;;) {
        const char *arg;
        char opt;

        rv = apr_getopt(gopt, "c:p:i:N:", &opt, &arg);
        if (APR_STATUS_IS_EOF(rv)) {
            break;
        } else if (rv) {
            usage();
        } else {
            switch (opt) {
            case 'c':
                command = arg;
                break;

            case 'p':
                port = atoi(arg);
                if (! port) {
                    usage();
                }
                break;

            case 'i':
                interface = arg;
                break;

            case 'N':
                num_to_start = atoi(arg);
                if (! num_to_start) {
                    usage();
                }
                break;

            default:
                break;
            }
        }
    }

    if (! command || ! port) {
        usage();
    }

    rv = apr_sockaddr_info_get(&skaddr, interface, APR_UNSPEC, port, 0, pool);
    if (rv) {
        exit_error(rv, "apr_sockaddr_info_get");
    }

    rv = apr_socket_create(&skt, skaddr->family, SOCK_STREAM, APR_PROTO_TCP, pool);
    if (rv) {
        exit_error(rv, "apr_socket_create");
    }

    rv = apr_socket_bind(skt, skaddr);
    if (rv) {
        exit_error(rv, "apr_socket_bind");
    }

    rv = apr_socket_listen(skt, 1024);
    if (rv) {
        exit_error(rv, "apr_socket_listen");
    }

    rv = apr_proc_detach(APR_PROC_DETACH_DAEMONIZE);
    if (rv) {
        exit_error(rv, "apr_proc_detach");
    }

#if defined(WIN32) || defined(OS2) || defined(NETWARE)

#error "Please implement me."

#else

    while (--num_to_start >= 0) {
        rv = apr_proc_fork(&proc, pool);
        if (rv == APR_INCHILD) {
            apr_os_file_t oft = 0;
            apr_os_sock_t oskt;

            /* Ok, so we need a file that has file descriptor 0 (which
             * FastCGI wants), but points to our socket.  This isn't really
             * possible in APR, so we cheat a bit.  I have no idea how to
             * do this on a non-unix platform, so for now this is platform
             * specific.  Ick.
             *
             * Note that this has to happen post-detach, otherwise fd 0
             * gets closed during apr_proc_detach and it's all for nothing.
             *
             * Unfortunately, doing this post detach means we have no way
             * to let anyone know if there's a problem at this point :( */

            rv = apr_os_file_put(&infd, &oft, APR_READ | APR_WRITE, pool);
            if (rv) {
                exit(EXIT_FAILURE);
            }

            rv = apr_os_sock_get(&oskt, skt);
            if (rv) {
                exit(EXIT_FAILURE);
            }

            rv = apr_os_file_put(&skwrapper, &oskt, APR_READ | APR_WRITE,
                                 pool);
            if (rv) {
                exit(EXIT_FAILURE);
            }

            rv = apr_file_dup2(infd, skwrapper, pool);
            if (rv) {
                exit(EXIT_FAILURE);
            }

            /* XXX Can't use apr_proc_create because there's no way to get
             *     infd into the procattr without going through another dup2,
             *     which means by the time it gets to the fastcgi process it
             *     is no longer fd 0, so it doesn't work.  Sigh. */

            execl(command, command, NULL);

        } else if (rv == APR_INPARENT) {
            if (num_to_start == 0) {
                apr_socket_close(skt);
            }
        } else {
            exit_error(rv, "apr_proc_fork");
        }
    }

#endif

    return EXIT_SUCCESS;
}
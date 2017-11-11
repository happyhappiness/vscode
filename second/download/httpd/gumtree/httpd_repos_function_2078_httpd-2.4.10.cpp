static apr_status_t socket_connect_un(apr_socket_t *sock,
                                      struct sockaddr_un *sa)
{
    apr_status_t rv;
    apr_os_sock_t rawsock;
    apr_interval_time_t t;

    rv = apr_os_sock_get(&rawsock, sock);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_socket_timeout_get(sock, &t);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    do {
        rv = connect(rawsock, (struct sockaddr*)sa,
                               sizeof(*sa) + strlen(sa->sun_path));
    } while (rv == -1 && errno == EINTR);

    if ((rv == -1) && (errno == EINPROGRESS || errno == EALREADY)
        && (t > 0)) {
#if APR_MAJOR_VERSION < 2
        rv = apr_wait_for_io_or_timeout(NULL, sock, 0);
#else
        rv = apr_socket_wait(sock, APR_WAIT_WRITE);
#endif

        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    if (rv == -1 && errno != EISCONN) {
        return errno;
    }

    return APR_SUCCESS;
}
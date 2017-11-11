static int is_socket_connected(apr_socket_t *socket)
{
    apr_pollfd_t pfds[1];
    apr_status_t status;
    apr_int32_t  nfds;

    pfds[0].reqevents = APR_POLLIN;
    pfds[0].desc_type = APR_POLL_SOCKET;
    pfds[0].desc.s = socket;

    do {
        status = apr_poll(&pfds[0], 1, &nfds, 0);
    } while (APR_STATUS_IS_EINTR(status));

    if (status == APR_SUCCESS && nfds == 1 &&
        pfds[0].rtnevents == APR_POLLIN) {
        apr_sockaddr_t unused;
        apr_size_t len = 1;
        char buf[1];
        /* The socket might be closed in which case
         * the poll will return POLLIN.
         * If there is no data available the socket
         * is closed.
         */
        status = apr_socket_recvfrom(&unused, socket, APR_MSG_PEEK,
                                     &buf[0], &len);
        if (status == APR_SUCCESS && len)
            return 1;
        else
            return 0;
    }
    else if (APR_STATUS_IS_EAGAIN(status) || APR_STATUS_IS_TIMEUP(status)) {
        return 1;
    }
    return 0;

}
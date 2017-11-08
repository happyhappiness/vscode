apr_status_t apr_socket_connect(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    int rc;        

    do {
        rc = connect(sock->socketdes,
                     (const struct sockaddr *)&sa->sa.sin,
                     sa->salen);
    } while (rc == -1 && errno == EINTR);

    /* we can see EINPROGRESS the first time connect is called on a non-blocking
     * socket; if called again, we can see EALREADY
     */
    if (rc == -1 && (errno == EINPROGRESS || errno == EALREADY) && sock->timeout != 0) {
        rc = apr_wait_for_io_or_timeout(NULL, sock, 0);
        if (rc != APR_SUCCESS) {
            return rc;
        }

#ifdef SO_ERROR
        {
            int error;
            apr_socklen_t len = sizeof(error);
            if ((rc = getsockopt(sock->socketdes, SOL_SOCKET, SO_ERROR, 
                                 (char *)&error, &len)) < 0) {
                return errno;
            }
            if (error) {
                return error;
            }
        }
#endif /* SO_ERROR */
    }

    if (rc == -1) {
        return errno;
    }

    sock->remote_addr = sa;
    if (sock->local_addr->port == 0) {
        /* connect() got us an ephemeral port */
        sock->local_port_unknown = 1;
    }
    if (!memcmp(sock->local_addr->ipaddr_ptr,
                generic_inaddr_any,
                sock->local_addr->ipaddr_len)) {
        /* not bound to specific local interface; connect() had to assign
         * one for the socket
         */
        sock->local_interface_unknown = 1;
    }
#ifndef HAVE_POLL
    sock->connected=1;
#endif
    return APR_SUCCESS;
}
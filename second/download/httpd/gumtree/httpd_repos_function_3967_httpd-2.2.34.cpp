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
    if ((rc == -1) && (errno == EINPROGRESS || errno == EALREADY)
                   && (sock->timeout > 0)) {
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


    if (memcmp(sa->ipaddr_ptr, generic_inaddr_any, sa->ipaddr_len)) {
        /* A real remote address was passed in.  If the unspecified
         * address was used, the actual remote addr will have to be
         * determined using getpeername() if required. */
        sock->remote_addr_unknown = 0;

        /* Copy the address structure details in. */
        sock->remote_addr->sa = sa->sa;
        sock->remote_addr->salen = sa->salen;
        /* Adjust ipaddr_ptr et al. */
        apr_sockaddr_vars_set(sock->remote_addr, sa->family, sa->port);
    }

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

    if (rc == -1 && errno != EISCONN) {
        return errno;
    }

#ifndef HAVE_POLL
    sock->connected=1;
#endif
    return APR_SUCCESS;
}
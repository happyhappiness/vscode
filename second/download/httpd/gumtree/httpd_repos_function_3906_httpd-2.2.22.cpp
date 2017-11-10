apr_status_t apr_socket_accept(apr_socket_t **new, apr_socket_t *sock,
                               apr_pool_t *connection_context)
{
    int s;
    apr_sockaddr_t sa;

    sa.salen = sizeof(sa.sa);

#ifdef HAVE_ACCEPT4
    s = accept4(sock->socketdes, (struct sockaddr *)&sa.sa, &sa.salen, SOCK_CLOEXEC);
#else
    s = accept(sock->socketdes, (struct sockaddr *)&sa.sa, &sa.salen);
#endif

    if (s < 0) {
        return errno;
    }
#ifdef TPF
    if (s == 0) { 
        /* 0 is an invalid socket for TPF */
        return APR_EINTR;
    }
#endif
    alloc_socket(new, connection_context);

    /* Set up socket variables -- note that it may be possible for
     * *new to be an AF_INET socket when sock is AF_INET6 in some
     * dual-stack configurations, so ensure that the remote_/local_addr
     * structures are adjusted for the family of the accepted
     * socket: */
    set_socket_vars(*new, sa.sa.sin.sin_family, SOCK_STREAM, sock->protocol);

#ifndef HAVE_POLL
    (*new)->connected = 1;
#endif
    (*new)->timeout = -1;

    (*new)->remote_addr_unknown = 0;

    (*new)->socketdes = s;

    /* Copy in peer's address. */
    (*new)->remote_addr->sa = sa.sa;
    (*new)->remote_addr->salen = sa.salen;

    *(*new)->local_addr = *sock->local_addr;

    /* The above assignment just overwrote the pool entry. Setting the local_addr 
       pool for the accepted socket back to what it should be.  Otherwise all 
       allocations for this socket will come from a server pool that is not
       freed until the process goes down.*/
    (*new)->local_addr->pool = connection_context;

    /* fix up any pointers which are no longer valid */
    if (sock->local_addr->sa.sin.sin_family == AF_INET) {
        (*new)->local_addr->ipaddr_ptr = &(*new)->local_addr->sa.sin.sin_addr;
    }
#if APR_HAVE_IPV6
    else if (sock->local_addr->sa.sin.sin_family == AF_INET6) {
        (*new)->local_addr->ipaddr_ptr = &(*new)->local_addr->sa.sin6.sin6_addr;
    }
#endif
    (*new)->remote_addr->port = ntohs((*new)->remote_addr->sa.sin.sin_port);
    if (sock->local_port_unknown) {
        /* not likely for a listening socket, but theoretically possible :) */
        (*new)->local_port_unknown = 1;
    }

#if APR_TCP_NODELAY_INHERITED
    if (apr_is_option_set(sock, APR_TCP_NODELAY) == 1) {
        apr_set_option(*new, APR_TCP_NODELAY, 1);
    }
#endif /* TCP_NODELAY_INHERITED */
#if APR_O_NONBLOCK_INHERITED
    if (apr_is_option_set(sock, APR_SO_NONBLOCK) == 1) {
        apr_set_option(*new, APR_SO_NONBLOCK, 1);
    }
#endif /* APR_O_NONBLOCK_INHERITED */

    if (sock->local_interface_unknown ||
        !memcmp(sock->local_addr->ipaddr_ptr,
                generic_inaddr_any,
                sock->local_addr->ipaddr_len)) {
        /* If the interface address inside the listening socket's local_addr wasn't 
         * up-to-date, we don't know local interface of the connected socket either.
         *
         * If the listening socket was not bound to a specific interface, we
         * don't know the local_addr of the connected socket.
         */
        (*new)->local_interface_unknown = 1;
    }

#ifndef HAVE_ACCEPT4
    {
        int flags;

        if ((flags = fcntl((*new)->socketdes, F_GETFD)) == -1)
            return errno;

        flags |= FD_CLOEXEC;
        if (fcntl((*new)->socketdes, F_SETFD, flags) == -1)
            return errno;
    }
#endif

    (*new)->inherit = 0;
    apr_pool_cleanup_register((*new)->pool, (void *)(*new), socket_cleanup,
                              socket_cleanup);
    return APR_SUCCESS;
}
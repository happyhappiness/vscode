apr_status_t apr_socket_opt_set(apr_socket_t *sock, 
                                apr_int32_t opt, apr_int32_t on)
{
    int one;
    apr_status_t rv;

    if (on)
        one = 1;
    else
        one = 0;
    switch(opt) {
    case APR_SO_KEEPALIVE:
#ifdef SO_KEEPALIVE
        if (on != apr_is_option_set(sock, APR_SO_KEEPALIVE)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_KEEPALIVE, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_KEEPALIVE, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_DEBUG:
        if (on != apr_is_option_set(sock, APR_SO_DEBUG)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_DEBUG, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_DEBUG, on);
        }
        break;
    case APR_SO_REUSEADDR:
        if (on != apr_is_option_set(sock, APR_SO_REUSEADDR)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_REUSEADDR, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_REUSEADDR, on);
        }
        break;
    case APR_SO_SNDBUF:
#ifdef SO_SNDBUF
        if (setsockopt(sock->socketdes, SOL_SOCKET, SO_SNDBUF, (void *)&on, sizeof(int)) == -1) {
            return errno;
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_RCVBUF:
#ifdef SO_RCVBUF
        if (setsockopt(sock->socketdes, SOL_SOCKET, SO_RCVBUF, (void *)&on, sizeof(int)) == -1) {
            return errno;
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_NONBLOCK:
        if (apr_is_option_set(sock, APR_SO_NONBLOCK) != on) {
            if (on) {
                if ((rv = sononblock(sock->socketdes)) != APR_SUCCESS) 
                    return rv;
            }
            else {
                if ((rv = soblock(sock->socketdes)) != APR_SUCCESS)
                    return rv;
            }
            apr_set_option(sock, APR_SO_NONBLOCK, on);
        }
        break;
    case APR_SO_LINGER:
#ifdef SO_LINGER
        if (apr_is_option_set(sock, APR_SO_LINGER) != on) {
            struct linger li;
            li.l_onoff = on;
            li.l_linger = APR_MAX_SECS_TO_LINGER;
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_LINGER, (char *) &li, sizeof(struct linger)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_SO_LINGER, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_TCP_DEFER_ACCEPT:
#if defined(TCP_DEFER_ACCEPT)
        if (apr_is_option_set(sock, APR_TCP_DEFER_ACCEPT) != on) {
            int optlevel = IPPROTO_TCP;
            int optname = TCP_DEFER_ACCEPT;

            if (setsockopt(sock->socketdes, optlevel, optname, 
                           (void *)&on, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_TCP_DEFER_ACCEPT, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_TCP_NODELAY:
#if defined(TCP_NODELAY)
        if (apr_is_option_set(sock, APR_TCP_NODELAY) != on) {
            int optlevel = IPPROTO_TCP;
            int optname = TCP_NODELAY;

#if APR_HAVE_SCTP
            if (sock->protocol == IPPROTO_SCTP) {
                optlevel = IPPROTO_SCTP;
                optname = SCTP_NODELAY;
            }
#endif
            if (setsockopt(sock->socketdes, optlevel, optname, (void *)&on, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(sock, APR_TCP_NODELAY, on);
        }
#else
        /* BeOS pre-BONE has TCP_NODELAY set by default.
         * As it can't be turned off we might as well check if they're asking
         * for it to be turned on!
         */
#ifdef BEOS
        if (on == 1)
            return APR_SUCCESS;
        else
#endif
        return APR_ENOTIMPL;
#endif
        break;
    case APR_TCP_NOPUSH:
#if APR_TCP_NOPUSH_FLAG
        /* TCP_N
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
        if (on != apr_is_option_set(sock->netmask, APR_SO_KEEPALIVE)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_KEEPALIVE, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(&sock->netmask,APR_SO_KEEPALIVE, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_DEBUG:
        if (on != apr_is_option_set(sock->netmask, APR_SO_DEBUG)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_DEBUG, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(&sock->netmask, APR_SO_DEBUG, on);
        }
        break;
    case APR_SO_REUSEADDR:
        if (on != apr_is_option_set(sock->netmask, APR_SO_REUSEADDR)) {
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_REUSEADDR, (void *)&one, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(&sock->netmask, APR_SO_REUSEADDR, on);
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
        if (apr_is_option_set(sock->netmask, APR_SO_NONBLOCK) != on) {
            if (on) {
                if ((rv = sononblock(sock->socketdes)) != APR_SUCCESS) 
                    return rv;
            }
            else {
                if ((rv = soblock(sock->socketdes)) != APR_SUCCESS)
                    return rv;
            }
            apr_set_option(&sock->netmask, APR_SO_NONBLOCK, on);
        }
        break;
    case APR_SO_LINGER:
#ifdef SO_LINGER
        if (apr_is_option_set(sock->netmask, APR_SO_LINGER) != on) {
            struct linger li;
            li.l_onoff = on;
            li.l_linger = APR_MAX_SECS_TO_LINGER;
            if (setsockopt(sock->socketdes, SOL_SOCKET, SO_LINGER, (char *) &li, sizeof(struct linger)) == -1) {
                return errno;
            }
            apr_set_option(&sock->netmask, APR_SO_LINGER, on);
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_SO_TIMEOUT:
        /* XXX: To be deprecated */
        return apr_socket_timeout_set(sock, on);
        break;
    case APR_TCP_NODELAY:
#if defined(TCP_NODELAY)
        if (apr_is_option_set(sock->netmask, APR_TCP_NODELAY) != on) {
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
            apr_set_option(&sock->netmask, APR_TCP_NODELAY, on);
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
        if (apr_is_option_set(sock->netmask, APR_TCP_NOPUSH) != on) {
            int optlevel = IPPROTO_TCP;
            int optname = TCP_NODELAY;

#if APR_HAVE_SCTP
            if (sock->protocol == IPPROTO_SCTP) {
                optlevel = IPPROTO_SCTP;
                optname = SCTP_NODELAY;
            }
#endif
            /* OK we're going to change some settings here... */
            /* TCP_NODELAY is mutually exclusive, so do we have it set? */
            if (apr_is_option_set(sock->netmask, APR_TCP_NODELAY) == 1 && on) {
                /* If we want to set NOPUSH then if we have the TCP_NODELAY
                 * flag set we need to switch it off...
                 */
                int tmpflag = 0;
                if (setsockopt(sock->socketdes, optlevel, optname,
                               (void*)&tmpflag, sizeof(int)) == -1) {
                    return errno;
                }
                apr_set_option(&sock->netmask, APR_RESET_NODELAY, 1);
                apr_set_option(&sock->netmask, APR_TCP_NODELAY, 0);
            } else if (on) {
                apr_set_option(&sock->netmask, APR_RESET_NODELAY, 0);
            }
            /* OK, now we can just set the TCP_NOPUSH flag accordingly...*/
            if (setsockopt(sock->socketdes, IPPROTO_TCP, APR_TCP_NOPUSH_FLAG,
                           (void*)&on, sizeof(int)) == -1) {
                return errno;
            }
            apr_set_option(&sock->netmask, APR_TCP_NOPUSH, on);
            if (!on && apr_is_option_set(sock->netmask, APR_RESET_NODELAY)) {
                int tmpflag = 1;
                if (setsockopt(sock->socketdes, optlevel, optname,
                               (void*)&tmpflag, sizeof(int)) == -1) {
                    return errno;
                }
                apr_set_option(&sock->netmask, APR_RESET_NODELAY,0);
                apr_set_option(&sock->netmask, APR_TCP_NODELAY, 1);
            }
        }
#else
        return APR_ENOTIMPL;
#endif
        break;
    case APR_INCOMPLETE_READ:
        apr_set_option(&sock->netmask, APR_INCOMPLETE_READ, on);
        break;
    case APR_IPV6_V6ONLY:
#if APR_HAVE_IPV6 && defined(IPV6_V6ONLY)
        /* we don't know the initial setting of this option,
         * so don't check sock->netmask since that optimization
         * won't work
         */
        if (setsockopt(sock->socketdes, IPPROTO_IPV6, IPV6_V6ONLY,
                       (void *)&on, sizeof(int)) == -1) {
            return errno;
        }
        apr_set_option(&sock->netmask, APR_IPV6_V6ONLY, on);
#else
        return APR_ENOTIMPL;
#endif
        break;
    default:
        return APR_EINVAL;
    }

    return APR_SUCCESS; 
}
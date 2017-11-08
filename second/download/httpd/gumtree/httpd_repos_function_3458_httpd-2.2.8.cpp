static apr_status_t do_mcast_opt(int type, apr_socket_t *sock,
                                 apr_byte_t value)
{
    apr_status_t rv = APR_SUCCESS;

    rv = mcast_check_type(sock);

    if (rv != APR_SUCCESS) {
        return rv;
    }

    if (sock_is_ipv4(sock)) {
        if (setsockopt(sock->socketdes, IPPROTO_IP, type,
                       (const void *) &value, sizeof(value)) == -1) {
            rv = errno;
        }
    }
#if APR_HAVE_IPV6
    else if (sock_is_ipv6(sock) && type == IP_MULTICAST_LOOP) {
        unsigned int loopopt = value;
        type = IPV6_MULTICAST_LOOP;
        if (setsockopt(sock->socketdes, IPPROTO_IPV6, type,
                       (const void *) &loopopt, sizeof(loopopt)) == -1) {
            rv = errno;
        }
    }
    else if (sock_is_ipv6(sock)) {
        if (type == IP_MULTICAST_TTL) {
            type = IPV6_MULTICAST_HOPS;
        }
        else {
            return APR_ENOTIMPL;
        }

        if (setsockopt(sock->socketdes, IPPROTO_IPV6, type,
                       &value, sizeof(value)) == -1) {
            rv = errno;
        }
    }
#endif
    else {
        rv = APR_ENOTIMPL;
    }

    return rv;
}
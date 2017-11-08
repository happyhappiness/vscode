static apr_status_t do_mcast_opt(int type, apr_socket_t *sock,
                                 apr_byte_t value)
{
    apr_status_t rv = APR_SUCCESS;

    if (sock_is_ipv4(sock)) {
        /* For the IP_MULTICAST_* options, this must be a (char *)
         * pointer. */
        if (setsockopt(sock->socketdes, IPPROTO_IP, type,
                       (const void *) &value, sizeof(value)) == -1) {
            rv = errno;
        }
    }
#if APR_HAVE_IPV6
    else if (sock_is_ipv6(sock)) {
        /* For the IPV6_* options, an (int *) pointer must be used. */
        int ivalue = value;

        if (type == IP_MULTICAST_TTL) {
            type = IPV6_MULTICAST_HOPS;
        }
        else if (type == IP_MULTICAST_LOOP) {
            type = IPV6_MULTICAST_LOOP;
        }
        else {
            return APR_ENOTIMPL;
        }

        if (setsockopt(sock->socketdes, IPPROTO_IPV6, type,
                       (const void *) &ivalue, sizeof(ivalue)) == -1) {
            rv = errno;
        }
    }
#endif
    else {
        rv = APR_ENOTIMPL;
    }

    return rv;
}
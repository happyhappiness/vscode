static apr_status_t do_mcast(int type, apr_socket_t *sock,
                             apr_sockaddr_t *mcast, apr_sockaddr_t *iface,
                             apr_sockaddr_t *source)
{
    struct ip_mreq mip4;
    apr_status_t rv = APR_SUCCESS;
#if APR_HAVE_IPV6
    struct ipv6_mreq mip6;
#endif
#ifdef GROUP_FILTER_SIZE
    struct group_source_req mip;
    int ip_proto;
#endif

    if (source != NULL) {
#ifdef GROUP_FILTER_SIZE
        if (sock_is_ipv4(sock)) {
            ip_proto = IPPROTO_IP;
        } 
#if APR_HAVE_IPV6
        else if (sock_is_ipv6(sock)) {
            ip_proto = IPPROTO_IPV6;
        }
#endif
        else {
            return APR_ENOTIMPL;
        }

        if (type == IP_ADD_MEMBERSHIP)
            type = MCAST_JOIN_SOURCE_GROUP;
        else if (type == IP_DROP_MEMBERSHIP)
            type = MCAST_LEAVE_SOURCE_GROUP;
        else
            return APR_ENOTIMPL;

        mip.gsr_interface = find_if_index(iface);
        memcpy(&mip.gsr_group, mcast->ipaddr_ptr, sizeof(mip.gsr_group));
        memcpy(&mip.gsr_source, source->ipaddr_ptr, sizeof(mip.gsr_source));

        if (setsockopt(sock->socketdes, ip_proto, type, (const void *) &mip,
                       sizeof(mip)) == -1) {
            rv = errno;
        }
#else
        /* We do not support Source-Specific Multicast. */
        return APR_ENOTIMPL;
#endif
    }
    else {
        if (sock_is_ipv4(sock)) {

            fill_mip_v4(&mip4, mcast, iface);

            if (setsockopt(sock->socketdes, IPPROTO_IP, type,
                           (const void *) &mip4, sizeof(mip4)) == -1) {
                rv = errno;
            }
        }
#if APR_HAVE_IPV6 && defined(IPV6_JOIN_GROUP) && defined(IPV6_LEAVE_GROUP)
        else if (sock_is_ipv6(sock)) {
            if (type == IP_ADD_MEMBERSHIP) {
                type = IPV6_JOIN_GROUP;
            }
            else if (type == IP_DROP_MEMBERSHIP) {
                type = IPV6_LEAVE_GROUP;
            }
            else {
                return APR_ENOTIMPL;
            }

            fill_mip_v6(&mip6, mcast, iface);

            if (setsockopt(sock->socketdes, IPPROTO_IPV6, type,
                           (const void *) &mip6, sizeof(mip6)) == -1) {
                rv = errno;
            }
        }
#endif
        else {
            rv = APR_ENOTIMPL;
        }
    }
    return rv;
}
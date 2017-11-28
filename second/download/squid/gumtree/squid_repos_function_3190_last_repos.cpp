bool
Ip::Intercept::NetfilterInterception(const Comm::ConnectionPointer &newConn, int silent)
{
#if LINUX_NETFILTER
    struct sockaddr_storage lookup;
    socklen_t len = newConn->local.isIPv6() ? sizeof(sockaddr_in6) : sizeof(sockaddr_in);
    newConn->local.getSockAddr(lookup, AF_UNSPEC);

    /** \par
     * Try NAT lookup for REDIRECT or DNAT targets. */
    if ( getsockopt(newConn->fd,
                    newConn->local.isIPv6() ? IPPROTO_IPV6 : IPPROTO_IP,
                    newConn->local.isIPv6() ? IP6T_SO_ORIGINAL_DST : SO_ORIGINAL_DST,
                    &lookup,
                    &len) != 0) {
        if (!silent) {
            int xerrno = errno;
            debugs(89, DBG_IMPORTANT, "ERROR: NF getsockopt(ORIGINAL_DST) failed on " << newConn << ": " << xstrerr(xerrno));
            lastReported_ = squid_curtime;
        }
        debugs(89, 9, "address: " << newConn);
        return false;
    } else {
        newConn->local = lookup;
        debugs(89, 5, "address NAT: " << newConn);
        return true;
    }
#endif
    return false;
}
bool
Ip::Intercept::NetfilterInterception(const Comm::ConnectionPointer &newConn, int silent)
{
#if LINUX_NETFILTER
    struct sockaddr_in lookup;
    socklen_t len = sizeof(struct sockaddr_in);
    newConn->local.GetSockAddr(lookup);

    /** \par
     * Try NAT lookup for REDIRECT or DNAT targets. */
    if ( getsockopt(newConn->fd, IPPROTO_IP, SO_ORIGINAL_DST, &lookup, &len) != 0) {
        if (!silent) {
            debugs(89, DBG_IMPORTANT, HERE << " NF getsockopt(SO_ORIGINAL_DST) failed on " << newConn << ": " << xstrerror());
            lastReported_ = squid_curtime;
        }
        debugs(89, 9, HERE << "address: " << newConn);
        return false;
    } else {
        newConn->local = lookup;
        debugs(89, 5, HERE << "address NAT: " << newConn);
        return true;
    }
#endif
    return false;
}
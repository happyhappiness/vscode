bool
Ip::Intercept::IpfwInterception(const Comm::ConnectionPointer &newConn, int silent)
{
#if IPFW_TRANSPARENT
    struct sockaddr_storage lookup;
    socklen_t len = sizeof(struct sockaddr_storage);
    newConn->local.GetSockAddr(lookup, AF_INET);

    /** \par
     * Try lookup for IPFW interception. */
    if ( getsockname(newConn->fd, (struct sockaddr*)&lookup, &len) != 0 ) {
        if ( !silent ) {
            debugs(89, DBG_IMPORTANT, HERE << " IPFW getsockname(...) failed: " << xstrerror());
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
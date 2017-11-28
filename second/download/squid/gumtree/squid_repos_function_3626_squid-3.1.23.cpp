int
IpIntercept::IpfwInterception(int fd, const IpAddress &me, IpAddress &dst, int silent)
{
#if IPFW_TRANSPARENT
    struct addrinfo *lookup = NULL;

    dst.GetAddrInfo(lookup,AF_INET);

    /** \par
     * Try lookup for IPFW interception. */
    if ( getsockname(fd, lookup->ai_addr, &lookup->ai_addrlen) != 0 ) {
        if ( !silent ) {
            debugs(89, DBG_IMPORTANT, HERE << " IPFW getsockname(...) failed: " << xstrerror());
            last_reported = squid_curtime;
        }
    } else {
        dst = *lookup;
    }

    dst.FreeAddrInfo(lookup);

    if (me != dst) {
        debugs(89, 5, HERE << "address NAT: me= " << me << ", dst= " << dst);
        return 0;
    }

    debugs(89, 9, HERE << "address: me= " << me << ", dst= " << dst);
#endif
    return -1;
}
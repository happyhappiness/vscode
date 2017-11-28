int
IpIntercept::NetfilterInterception(int fd, const IpAddress &me, IpAddress &dst, int silent)
{
#if LINUX_NETFILTER
    struct addrinfo *lookup = NULL;

    dst.GetAddrInfo(lookup,AF_INET);

    /** \par
     * Try NAT lookup for REDIRECT or DNAT targets. */
    if ( getsockopt(fd, IPPROTO_IP, SO_ORIGINAL_DST, lookup->ai_addr, &lookup->ai_addrlen) != 0) {
        if (!silent) {
            debugs(89, DBG_IMPORTANT, HERE << " NF getsockopt(SO_ORIGINAL_DST) failed on FD " << fd << ": " << xstrerror());
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
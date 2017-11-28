void
Ip::Address::getSockAddr(struct sockaddr_storage &addr, const int family) const
{
    struct sockaddr_in *sin = NULL;

    if ( family == AF_INET && !isIPv4()) {
        // FIXME INET6: caller using the wrong socket type!
        debugs(14, DBG_CRITICAL, HERE << "Ip::Address::getSockAddr : Cannot convert non-IPv4 to IPv4. from " << *this);
        assert(false);
    }

    if ( family == AF_INET6 || (family == AF_UNSPEC && isIPv6()) ) {
        struct sockaddr_in6 *ss6 = (struct sockaddr_in6*)&addr;
        getSockAddr(*ss6);
    } else if ( family == AF_INET || (family == AF_UNSPEC && isIPv4()) ) {
        sin = (struct sockaddr_in*)&addr;
        getSockAddr(*sin);
    } else {
        IASSERT("false",false);
    }
}
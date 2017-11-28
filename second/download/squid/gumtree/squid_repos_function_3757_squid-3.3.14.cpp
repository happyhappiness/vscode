void
Ip::Address::GetSockAddr(struct sockaddr_storage &addr, const int family) const
{
    struct sockaddr_in *sin = NULL;

    if ( family == AF_INET && !IsIPv4()) {
        // FIXME INET6: caller using the wrong socket type!
        debugs(14, DBG_CRITICAL, HERE << "Ip::Address::GetSockAddr : Cannot convert non-IPv4 to IPv4. from " << *this);
        assert(false);
    }

    if ( family == AF_INET6 || (family == AF_UNSPEC && IsIPv6()) ) {
        struct sockaddr_in6 *ss6 = (struct sockaddr_in6*)&addr;
        GetSockAddr(*ss6);
    } else if ( family == AF_INET || (family == AF_UNSPEC && IsIPv4()) ) {
        sin = (struct sockaddr_in*)&addr;
        GetSockAddr(*sin);
    } else {
        IASSERT("false",false);
    }
}
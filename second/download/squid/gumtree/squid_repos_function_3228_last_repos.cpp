void
Ip::Address::getAddrInfo(struct addrinfo *&dst, int force) const
{
    if (dst == NULL) {
        dst = new addrinfo;
    }

    memset(dst, 0, sizeof(struct addrinfo));

    // set defaults
    // Mac OS X does not emit a flag indicating the output is numeric (IP address)
#if _SQUID_APPLE_
    dst->ai_flags = 0;
#else
    dst->ai_flags = AI_NUMERICHOST;
#endif

    if (dst->ai_socktype == 0)
        dst->ai_socktype = SOCK_STREAM;

    if (dst->ai_socktype == SOCK_STREAM // implies TCP
            && dst->ai_protocol == 0)
        dst->ai_protocol = IPPROTO_TCP;

    if (dst->ai_socktype == SOCK_DGRAM // implies UDP
            && dst->ai_protocol == 0)
        dst->ai_protocol = IPPROTO_UDP;

    if (force == AF_INET6 || (force == AF_UNSPEC && Ip::EnableIpv6 && isIPv6()) ) {
        dst->ai_addr = (struct sockaddr*)new sockaddr_in6;

        memset(dst->ai_addr,0,sizeof(struct sockaddr_in6));

        getSockAddr(*((struct sockaddr_in6*)dst->ai_addr));

        dst->ai_addrlen = sizeof(struct sockaddr_in6);

        dst->ai_family = ((struct sockaddr_in6*)dst->ai_addr)->sin6_family;

#if 0
        /**
         * Enable only if you must and please report to squid-dev if you find a need for this.
         *
         * Vista may need this to cope with dual-stack (unsetting IP6_V6ONLY).
         *         http://msdn.microsoft.com/en-us/library/ms738574(VS.85).aspx
         * Linux appears to only do some things when its present.
         *         (93) Bad Protocol
         * FreeBSD dies horribly when using dual-stack with it set.
         *         (43) Protocol not supported
         */
        dst->ai_protocol = IPPROTO_IPV6;
#endif

    } else if ( force == AF_INET || (force == AF_UNSPEC && isIPv4()) ) {

        dst->ai_addr = (struct sockaddr*)new sockaddr_in;

        memset(dst->ai_addr,0,sizeof(struct sockaddr_in));

        getSockAddr(*((struct sockaddr_in*)dst->ai_addr));

        dst->ai_addrlen = sizeof(struct sockaddr_in);

        dst->ai_family = ((struct sockaddr_in*)dst->ai_addr)->sin_family;
    } else {
        IASSERT("false",false);
    }
}
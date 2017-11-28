void
Ip::Address::setLocalhost()
{
    if (Ip::EnableIpv6) {
        mSocketAddr_.sin6_addr = in6addr_loopback;
        mSocketAddr_.sin6_family = AF_INET6;
    } else {
        mSocketAddr_.sin6_addr = v4_localhost;
        mSocketAddr_.sin6_family = AF_INET;
    }
}
bool
Ip::Address::getReverseString(char buf[MAX_IPSTRLEN], int show_type) const
{

    if (show_type == AF_UNSPEC) {
        show_type = isIPv6() ? AF_INET6 : AF_INET ;
    }

    if (show_type == AF_INET && isIPv4()) {
        struct in_addr* tmp = (struct in_addr*)&mSocketAddr_.sin6_addr.s6_addr[12];
        return getReverseString4(buf, *tmp);
    } else if ( show_type == AF_INET6 && isIPv6() ) {
        return getReverseString6(buf, mSocketAddr_.sin6_addr);
    }

    debugs(14, DBG_CRITICAL, "Unable to convert '" << toStr(buf,MAX_IPSTRLEN) << "' to the rDNS type requested.");

    buf[0] = '\0';

    return false;
}
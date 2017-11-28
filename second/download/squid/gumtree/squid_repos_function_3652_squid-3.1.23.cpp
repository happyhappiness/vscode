bool IpAddress::GetReverseString(char buf[MAX_IPSTRLEN], int show_type) const
{

    if (show_type == AF_UNSPEC) {
        show_type = IsIPv6() ? AF_INET6 : AF_INET ;
    }

    if (show_type == AF_INET && IsIPv4()) {
        struct in_addr* tmp = (struct in_addr*)&m_SocketAddr.sin6_addr.s6_addr[12];
        return GetReverseString4(buf, *tmp);
    } else if ( show_type == AF_INET6 && IsIPv6() ) {
        return GetReverseString6(buf, m_SocketAddr.sin6_addr);
    }

    debugs(14,0, "Unable to convert '" << NtoA(buf,MAX_IPSTRLEN) << "' to the rDNS type requested.");

    buf[0] = '\0';

    return false;
}
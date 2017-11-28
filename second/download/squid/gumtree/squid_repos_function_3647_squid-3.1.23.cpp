void IpAddress::SetLocalhost()
{
    if (Ip::EnableIpv6) {
        m_SocketAddr.sin6_addr = in6addr_loopback;
        m_SocketAddr.sin6_family = AF_INET6;
    } else {
        m_SocketAddr.sin6_addr = v4_localhost;
        m_SocketAddr.sin6_family = AF_INET;
    }
}
bool IpAddress::IsLocalhost() const
{
    return IN6_IS_ADDR_LOOPBACK( &m_SocketAddr.sin6_addr ) || IN6_ARE_ADDR_EQUAL( &m_SocketAddr.sin6_addr, &v4_localhost );
}
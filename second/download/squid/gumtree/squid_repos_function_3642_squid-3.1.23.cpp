bool IpAddress::IsAnyAddr() const
{
    return IN6_IS_ADDR_UNSPECIFIED( &m_SocketAddr.sin6_addr );
}
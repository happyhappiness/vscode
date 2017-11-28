bool
Ip::Address::IsIPv4() const
{
    return IN6_IS_ADDR_V4MAPPED( &m_SocketAddr.sin6_addr );
}
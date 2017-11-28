void
Ip::Address::SetNoAddr()
{
    memset(&m_SocketAddr.sin6_addr, 0xFF, sizeof(struct in6_addr) );
    m_SocketAddr.sin6_family = AF_INET6;
}
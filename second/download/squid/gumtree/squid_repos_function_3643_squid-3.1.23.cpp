void IpAddress::SetAnyAddr()
{
    memset(&m_SocketAddr.sin6_addr, 0, sizeof(struct in6_addr) );
}
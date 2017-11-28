void IpAddress::SetEmpty()
{
    memset(&m_SocketAddr, 0, sizeof(m_SocketAddr) );
}
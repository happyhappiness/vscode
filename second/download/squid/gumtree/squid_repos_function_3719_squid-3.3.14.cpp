void
Ip::Address::SetEmpty()
{
    memset(&m_SocketAddr, 0, sizeof(m_SocketAddr) );
}
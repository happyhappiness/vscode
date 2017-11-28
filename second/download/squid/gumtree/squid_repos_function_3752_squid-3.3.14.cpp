unsigned short
Ip::Address::GetPort() const
{
    return ntohs( m_SocketAddr.sin6_port );
}
unsigned short
IpAddress::GetPort() const
{
    return ntohs( m_SocketAddr.sin6_port );
}
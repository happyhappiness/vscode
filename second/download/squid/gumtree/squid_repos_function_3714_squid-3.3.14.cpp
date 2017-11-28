bool
Ip::Address::IsSockAddr() const
{
    return (m_SocketAddr.sin6_port != 0);
}
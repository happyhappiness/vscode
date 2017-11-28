IpAddress& IpAddress::operator =(struct sockaddr_in const &s)
{
    Map4to6((const in_addr)s.sin_addr, m_SocketAddr.sin6_addr);
    m_SocketAddr.sin6_port = s.sin_port;
    m_SocketAddr.sin6_family = AF_INET6;
    return *this;
}
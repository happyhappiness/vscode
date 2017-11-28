IpAddress& IpAddress::operator =(struct in_addr const &s)
{
    Map4to6((const in_addr)s, m_SocketAddr.sin6_addr);
    m_SocketAddr.sin6_family = AF_INET6;
    return *this;
}
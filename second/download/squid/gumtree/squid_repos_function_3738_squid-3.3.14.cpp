Ip::Address &
Ip::Address::operator =(struct in6_addr const &s)
{

    memcpy(&m_SocketAddr.sin6_addr, &s, sizeof(struct in6_addr));
    m_SocketAddr.sin6_family = AF_INET6;

    return *this;
}
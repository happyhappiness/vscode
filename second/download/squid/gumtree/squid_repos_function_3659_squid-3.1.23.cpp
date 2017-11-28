IpAddress& IpAddress::operator =(struct sockaddr_in6 const &s)
{
    memcpy(&m_SocketAddr, &s, sizeof(struct sockaddr_in6));

    return *this;
}
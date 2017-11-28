Ip::Address &
Ip::Address::operator =(struct sockaddr_in const &s)
{
    map4to6((const in_addr)s.sin_addr, mSocketAddr_.sin6_addr);
    mSocketAddr_.sin6_port = s.sin_port;
    mSocketAddr_.sin6_family = AF_INET6;
    return *this;
}
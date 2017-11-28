Ip::Address &
Ip::Address::operator =(struct in_addr const &s)
{
    map4to6((const in_addr)s, mSocketAddr_.sin6_addr);
    mSocketAddr_.sin6_family = AF_INET6;
    return *this;
}
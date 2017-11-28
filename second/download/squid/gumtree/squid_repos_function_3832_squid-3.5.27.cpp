Ip::Address &
Ip::Address::operator =(struct in6_addr const &s)
{

    memcpy(&mSocketAddr_.sin6_addr, &s, sizeof(struct in6_addr));
    mSocketAddr_.sin6_family = AF_INET6;

    return *this;
}
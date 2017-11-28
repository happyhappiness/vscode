Ip::Address &
Ip::Address::operator =(struct sockaddr_in6 const &s)
{
    memcpy(&mSocketAddr_, &s, sizeof(struct sockaddr_in6));

    return *this;
}
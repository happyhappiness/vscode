void
Ip::Address::setAnyAddr()
{
    memset(&mSocketAddr_.sin6_addr, 0, sizeof(struct in6_addr) );
}
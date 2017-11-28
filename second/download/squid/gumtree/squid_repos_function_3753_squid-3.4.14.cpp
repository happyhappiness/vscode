void
Ip::Address::setNoAddr()
{
    memset(&mSocketAddr_.sin6_addr, 0xFF, sizeof(struct in6_addr) );
    mSocketAddr_.sin6_family = AF_INET6;
}
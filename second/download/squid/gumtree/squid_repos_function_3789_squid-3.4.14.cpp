void
Ip::Address::getInAddr(struct in6_addr &buf) const
{
    memcpy(&buf, &mSocketAddr_.sin6_addr, sizeof(struct in6_addr));
}
bool
Ip::Address::isIPv4() const
{
    return IN6_IS_ADDR_V4MAPPED( &mSocketAddr_.sin6_addr );
}
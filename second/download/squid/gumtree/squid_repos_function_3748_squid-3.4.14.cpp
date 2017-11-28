bool
Ip::Address::isLocalhost() const
{
    return IN6_IS_ADDR_LOOPBACK( &mSocketAddr_.sin6_addr ) || IN6_ARE_ADDR_EQUAL( &mSocketAddr_.sin6_addr, &v4_localhost );
}
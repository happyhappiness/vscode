bool
Ip::Address::isAnyAddr() const
{
    return IN6_IS_ADDR_UNSPECIFIED(&mSocketAddr_.sin6_addr) || IN6_ARE_ADDR_EQUAL(&mSocketAddr_.sin6_addr, &v4_anyaddr);
}
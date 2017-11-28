bool
Ip::Address::isSiteLocal6() const
{
    // RFC 4193 the site-local allocated range is fc00::/7
    // with fd00::/8 as the only currently allocated range (so we test it first).
    // BUG: as of 2010-02 Linux and BSD define IN6_IS_ADDR_SITELOCAL() to check for fec::/10
    return mSocketAddr_.sin6_addr.s6_addr[0] == static_cast<uint8_t>(0xfd) ||
           mSocketAddr_.sin6_addr.s6_addr[0] == static_cast<uint8_t>(0xfc);
}
bool
Ip::Address::isSiteLocalAuto() const
{
    return mSocketAddr_.sin6_addr.s6_addr[11] == static_cast<uint8_t>(0xff) &&
           mSocketAddr_.sin6_addr.s6_addr[12] == static_cast<uint8_t>(0xfe);
}
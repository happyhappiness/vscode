bool
Ip::Address::ApplyMask(const unsigned int cidr, int mtype)
{
    uint8_t clearbits = 0;
    uint8_t* p = NULL;

    // validation and short-cuts.
    if (cidr > 128)
        return false;

    if (cidr > 32 && mtype == AF_INET)
        return false;

    if (cidr == 0) {
        /* CIDR /0 is NoAddr regardless of the IPv4/IPv6 protocol */
        SetNoAddr();
        return true;
    }

    clearbits = (uint8_t)( (mtype==AF_INET6?128:32) -cidr);

    // short-cut
    if (clearbits == 0)
        return true;

    p = (uint8_t*)(&m_SocketAddr.sin6_addr) + 15;

    for (; clearbits>0 && p >= (uint8_t*)&m_SocketAddr.sin6_addr ; --p ) {
        if (clearbits < 8) {
            *p &= ((0xFF << clearbits) & 0xFF);
            clearbits = 0;
        } else {
            *p &= 0x00;
            clearbits -= 8;
        }
    }

    return true;
}
bool
Ip::Address::applyMask(const unsigned int cidrMask, int mtype)
{
    uint8_t clearbits = 0;
    uint8_t* p = NULL;

    // validation and short-cuts.
    if (cidrMask > 128)
        return false;

    if (cidrMask > 32 && mtype == AF_INET)
        return false;

    if (cidrMask == 0) {
        /* CIDR /0 is NoAddr regardless of the IPv4/IPv6 protocol */
        setNoAddr();
        return true;
    }

    clearbits = (uint8_t)( (mtype==AF_INET6?128:32) - cidrMask);

    // short-cut
    if (clearbits == 0)
        return true;

    p = (uint8_t*)(&mSocketAddr_.sin6_addr) + 15;

    for (; clearbits>0 && p >= (uint8_t*)&mSocketAddr_.sin6_addr ; --p ) {
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
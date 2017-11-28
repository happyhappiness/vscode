int
Ip::Address::cidr() const
{
    uint8_t shift,ipbyte;
    uint8_t bit,caught;
    int len = 0;
    const uint8_t *ptr= mSocketAddr_.sin6_addr.s6_addr;

    /* Let's scan all the bits from Most Significant to Least */
    /* Until we find an "0" bit. Then, we return */
    shift=0;

    /* return IPv4 CIDR for any Mapped address */
    /* Thus only check the mapped bit */

    if ( !isIPv6() ) {
        shift = 12;
    }

    for (; shift<sizeof(mSocketAddr_.sin6_addr) ; ++shift) {
        ipbyte= *(ptr+shift);

        if (ipbyte == 0xFF) {
            len += 8;
            continue ;  /* A short-cut */
        }

        for (caught = 0 , bit= 7 ; !caught && (bit <= 7); --bit) {
            caught = ((ipbyte & 0x80) == 0x00);  /* Found a '0' at 'bit' ? */

            if (!caught)
                ++len;

            ipbyte <<= 1;
        }

        if (caught)
            break; /* We have found the most significant "0" bit.  */
    }

    return len;
}
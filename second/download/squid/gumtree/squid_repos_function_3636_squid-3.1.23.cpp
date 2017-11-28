int
IpAddress::GetCIDR() const
{
    uint8_t shift,byte;
    uint8_t bit,caught;
    int len = 0;
    const uint8_t *ptr= m_SocketAddr.sin6_addr.s6_addr;

    /* Let's scan all the bits from Most Significant to Least */
    /* Until we find an "0" bit. Then, we return */
    shift=0;

    /* return IPv4 CIDR for any Mapped address */
    /* Thus only check the mapped bit */

    if ( !IsIPv6() ) {
        shift = 12;
    }

    for (; shift<sizeof(m_SocketAddr.sin6_addr) ; shift++) {
        byte= *(ptr+shift);

        if (byte == 0xFF) {
            len += 8;
            continue ;  /* A short-cut */
        }

        for (caught = 0 , bit= 7 ; !caught && (bit <= 7); bit--) {
            caught = ((byte & 0x80) == 0x00);  /* Found a '0' at 'bit' ? */

            if (!caught)
                len++;

            byte <<= 1;
        }

        if (caught)
            break; /* We have found the most significant "0" bit.  */
    }

    return len;
}
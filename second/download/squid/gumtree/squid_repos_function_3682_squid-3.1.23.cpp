void IpAddress::Map4to6(const struct in_addr &in, struct in6_addr &out) const
{
    /* check for special cases */

    if ( in.s_addr == 0x00000000) {
        /* ANYADDR */
        out = v4_anyaddr;
    } else if ( in.s_addr == 0xFFFFFFFF) {
        /* NOADDR */
        out = v4_noaddr;
    } else {
        /* general */
        out = v4_anyaddr;
        out.s6_addr[12] = ((uint8_t *)&in.s_addr)[0];
        out.s6_addr[13] = ((uint8_t *)&in.s_addr)[1];
        out.s6_addr[14] = ((uint8_t *)&in.s_addr)[2];
        out.s6_addr[15] = ((uint8_t *)&in.s_addr)[3];
    }
}
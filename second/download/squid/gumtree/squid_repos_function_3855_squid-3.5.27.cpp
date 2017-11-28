void
Ip::Address::map6to4(const struct in6_addr &in, struct in_addr &out) const
{
    /* ANYADDR */
    /* NOADDR */
    /* general */

    memset(&out, 0, sizeof(struct in_addr));
    ((uint8_t *)&out.s_addr)[0] = in.s6_addr[12];
    ((uint8_t *)&out.s_addr)[1] = in.s6_addr[13];
    ((uint8_t *)&out.s_addr)[2] = in.s6_addr[14];
    ((uint8_t *)&out.s_addr)[3] = in.s6_addr[15];
}
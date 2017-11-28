bool
Ip::Address::GetReverseString6(char buf[MAX_IPSTRLEN], const struct in6_addr &dat) const
{
    char *p = buf;
    unsigned char const *r = dat.s6_addr;

    /* RFC1886 says: */
    /*     4321:0:1:2:3:4:567:89ab */
    /*     must be sent */
    /*     b.a.9.8.7.6.5.0.4.0.0.0.3.0.0.0.2.0.0.0.1.0.0.0.0.0.0.0.1.2.3.4.ip6.int. */

    /* Work from the binary field. Anything else may have representation changes. */
    /* The sin6_port and sin6_addr members shall be in network byte order. */

    /* Compile Err: 'Too many arguments for format. */

    for (int i = 15; i >= 0; --i, p+=4) {
        snprintf(p, 5, "%x.%x.", ((r[i])&0xf), (((r[i])>>4)&0xf) );
    }

    /* RFC3152 says: */
    /*     ip6.int is now deprecated TLD, use ip6.arpa instead. */
    snprintf(p,10,"ip6.arpa.");

    return true;
}
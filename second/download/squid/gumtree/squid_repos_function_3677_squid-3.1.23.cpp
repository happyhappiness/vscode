unsigned int IpAddress::ToHostname(char *buf, const unsigned int blen) const
{
    char *p = buf;

    if (IsIPv6() && blen > 0) {
        *p = '[';
        p++;
    }

    /* 8 being space for [ ] : and port digits */
    if ( IsIPv6() )
        NtoA(p, blen-8, AF_INET6);
    else
        NtoA(p, blen-8, AF_INET);

    // find the end of the new string
    while (*p != '\0' && p < buf+blen)
        p++;

    if (IsIPv6() && p < (buf+blen-1) ) {
        *p = ']';
        p++;
    }

    /* terminate just in case. */
    *p = '\0';

    /* return size of buffer now used */
    return (p - buf);
}
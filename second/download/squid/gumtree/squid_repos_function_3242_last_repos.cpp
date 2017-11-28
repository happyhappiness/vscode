unsigned int
Ip::Address::toHostStr(char *buf, const unsigned int blen) const
{
    char *p = buf;

    if (isIPv6() && blen > 0) {
        *p = '[';
        ++p;
    }

    /* 8 being space for [ ] : and port digits */
    if ( isIPv6() )
        toStr(p, blen-8, AF_INET6);
    else
        toStr(p, blen-8, AF_INET);

    // find the end of the new string
    while (*p != '\0' && p < buf+blen)
        ++p;

    if (isIPv6() && p < (buf+blen-1) ) {
        *p = ']';
        ++p;
    }

    /* terminate just in case. */
    *p = '\0';

    /* return size of buffer now used */
    return (p - buf);
}
static int
aclHostDomainCompare( char *const &a, char * const &b)
{
    const char *h = static_cast<const char *>(a);
    const char *d = static_cast<const char *>(b);
    return matchDomainName(h, d);
}
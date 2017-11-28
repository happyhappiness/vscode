ssize_t
rfc3596BuildPTRQuery4(const struct in_addr addr, char *buf, size_t sz, unsigned short qid, rfc1035_query * query)
{
    static char rev[RFC1035_MAXHOSTNAMESZ];
    unsigned int i;

    i = (unsigned int) ntohl(addr.s_addr);
    snprintf(rev, RFC1035_MAXHOSTNAMESZ, "%u.%u.%u.%u.in-addr.arpa.",
             i & 255,
             (i >> 8) & 255,
             (i >> 16) & 255,
             (i >> 24) & 255);

    return rfc3596BuildHostQuery(rev, buf, sz, qid, query, RFC1035_TYPE_PTR);
}
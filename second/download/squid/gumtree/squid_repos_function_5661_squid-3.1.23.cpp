ssize_t
rfc3596BuildPTRQuery6(const struct in6_addr addr, char *buf, size_t sz, unsigned short qid, rfc1035_query * query)
{
    static char rev[RFC1035_MAXHOSTNAMESZ];
    const uint8_t* r = addr.s6_addr;
    char* p = rev;
    int i; /* NP: MUST allow signed for loop termination. */

    /* work from the raw addr field. anything else may have representation changes. */
    /* The sin6_port and sin6_addr members shall be in network byte order. */
    for (i = 15; i >= 0; i--, p+=4) {
        snprintf(p, 5, "%1x.%1x.", ((r[i])&0xf), (r[i]>>4)&0xf );
    }

    snprintf(p,10,"ip6.arpa.");

    return rfc3596BuildHostQuery(rev, buf, sz, qid, query, RFC1035_TYPE_PTR);
}
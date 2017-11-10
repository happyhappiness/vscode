static apr_status_t parse_network(apr_ipsubnet_t *ipsub, const char *network)
{
    /* legacy syntax for ip addrs: a.b.c. ==> a.b.c.0/24 for example */
    int shift;
    char *s, *t;
    int octet;
    char buf[sizeof "255.255.255.255"];

    if (strlen(network) < sizeof buf) {
        strcpy(buf, network);
    }
    else {
        return APR_EBADIP;
    }

    /* parse components */
    s = buf;
    ipsub->sub[0] = 0;
    ipsub->mask[0] = 0;
    shift = 24;
    while (*s) {
        t = s;
        if (!apr_isdigit(*t)) {
            return APR_EBADIP;
        }
        while (apr_isdigit(*t)) {
            ++t;
        }
        if (*t == '.') {
            *t++ = 0;
        }
        else if (*t) {
            return APR_EBADIP;
        }
        if (shift < 0) {
            return APR_EBADIP;
        }
        octet = atoi(s);
        if (octet < 0 || octet > 255) {
            return APR_EBADIP;
        }
        ipsub->sub[0] |= octet << shift;
        ipsub->mask[0] |= 0xFFUL << shift;
        s = t;
        shift -= 8;
    }
    ipsub->sub[0] = ntohl(ipsub->sub[0]);
    ipsub->mask[0] = ntohl(ipsub->mask[0]);
    ipsub->family = AF_INET;
    return APR_SUCCESS;
}
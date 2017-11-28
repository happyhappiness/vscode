static int
rfc1035QueryUnpack(const char *buf, size_t sz, unsigned int *off, rfc1035_query * query)
{
    unsigned short s;
    if (rfc1035NameUnpack(buf, sz, off, NULL, query->name, RFC1035_MAXHOSTNAMESZ, 0)) {
        RFC1035_UNPACK_DEBUG;
        memset(query, '\0', sizeof(*query));
        return 1;
    }
    if (*off + 4 > sz) {
        RFC1035_UNPACK_DEBUG;
        memset(query, '\0', sizeof(*query));
        return 1;
    }
    memcpy(&s, buf + *off, 2);
    *off += 2;
    query->qtype = ntohs(s);
    memcpy(&s, buf + *off, 2);
    *off += 2;
    query->qclass = ntohs(s);
    return 0;
}
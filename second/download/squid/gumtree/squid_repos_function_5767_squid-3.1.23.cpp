ssize_t
rfc1035BuildPTRQuery(const struct in_addr addr, char *buf, size_t sz, unsigned short qid, rfc1035_query * query)
{
    static rfc1035_message h;
    size_t offset = 0;
    static char rev[32];
    unsigned int i;
    memset(&h, '\0', sizeof(h));
    i = (unsigned int) ntohl(addr.s_addr);
    snprintf(rev, 32, "%u.%u.%u.%u.in-addr.arpa.",
             i & 255,
             (i >> 8) & 255,
             (i >> 16) & 255,
             (i >> 24) & 255);
    h.id = qid;
    h.qr = 0;
    h.rd = 1;
    h.opcode = 0;		/* QUERY */
    h.qdcount = (unsigned int) 1;
    offset += rfc1035HeaderPack(buf + offset, sz - offset, &h);
    offset += rfc1035QuestionPack(buf + offset,
                                  sz - offset,
                                  rev,
                                  RFC1035_TYPE_PTR,
                                  RFC1035_CLASS_IN);
    if (query) {
        query->qtype = RFC1035_TYPE_PTR;
        query->qclass = RFC1035_CLASS_IN;
        xstrncpy(query->name, rev, sizeof(query->name));
    }
    assert(offset <= sz);
    return offset;
}
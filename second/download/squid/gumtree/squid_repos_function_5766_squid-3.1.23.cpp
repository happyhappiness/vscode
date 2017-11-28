ssize_t
rfc1035BuildAQuery(const char *hostname, char *buf, size_t sz, unsigned short qid, rfc1035_query * query)
{
    static rfc1035_message h;
    size_t offset = 0;
    memset(&h, '\0', sizeof(h));
    h.id = qid;
    h.qr = 0;
    h.rd = 1;
    h.opcode = 0;		/* QUERY */
    h.qdcount = (unsigned int) 1;
    offset += rfc1035HeaderPack(buf + offset, sz - offset, &h);
    offset += rfc1035QuestionPack(buf + offset,
                                  sz - offset,
                                  hostname,
                                  RFC1035_TYPE_A,
                                  RFC1035_CLASS_IN);
    if (query) {
        query->qtype = RFC1035_TYPE_A;
        query->qclass = RFC1035_CLASS_IN;
        xstrncpy(query->name, hostname, sizeof(query->name));
    }
    assert(offset <= sz);
    return offset;
}
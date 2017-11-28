int
rfc1035RRPack(char *buf, const size_t sz, const rfc1035_rr * RR)
{
    unsigned int off;
    uint16_t s;
    uint32_t i;

    off = rfc1035NamePack(buf, sz, RR->name);

    /*
     * Make sure the remaining message has enough octets for the
     * rest of the RR fields.
     */
    if ((off + sizeof(s)*3 + sizeof(i) + RR->rdlength) > sz) {
        return 0;
    }
    s = htons(RR->type);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    s = htons(RR->_class);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    i = htonl(RR->ttl);
    memcpy(buf + off, &i, sizeof(i));
    off += sizeof(i);
    s = htons(RR->rdlength);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    memcpy(buf + off, &(RR->rdata), RR->rdlength);
    off += RR->rdlength;
    assert(off <= sz);
    return off;
}
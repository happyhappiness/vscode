int
rfc1035HeaderUnpack(const char *buf, size_t sz, unsigned int *off, rfc1035_message * h)
{
    unsigned short s;
    unsigned short t;
    assert(*off == 0);
    /*
     * The header is 12 octets.  This is a bogus message if the size
     * is less than that.
     */
    if (sz < 12)
        return 1;
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    h->id = ntohs(s);
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    t = ntohs(s);
    h->qr = (t >> 15) & 0x01;
    h->opcode = (t >> 11) & 0x0F;
    h->aa = (t >> 10) & 0x01;
    h->tc = (t >> 9) & 0x01;
    h->rd = (t >> 8) & 0x01;
    h->ra = (t >> 7) & 0x01;
    /*
     * We might want to check that the reserved 'Z' bits (6-4) are
     * all zero as per RFC 1035.  If not the message should be
     * rejected.
     * NO! RFCs say ignore inbound reserved, they may be used in future.
     *  NEW messages need to be set 0, thats all.
     */
    h->rcode = t & 0x0F;
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    h->qdcount = ntohs(s);
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    h->ancount = ntohs(s);
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    h->nscount = ntohs(s);
    memcpy(&s, buf + (*off), sizeof(s));
    (*off) += sizeof(s);
    h->arcount = ntohs(s);
    assert((*off) == 12);
    return 0;
}
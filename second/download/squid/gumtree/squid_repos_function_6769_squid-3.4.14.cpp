int
rfc1035HeaderPack(char *buf, size_t sz, rfc1035_message * hdr)
{
    int off = 0;
    unsigned short s;
    unsigned short t;
    assert(sz >= 12);
    s = htons(hdr->id);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    t = 0;
    t |= hdr->qr << 15;
    t |= (hdr->opcode << 11);
    t |= (hdr->aa << 10);
    t |= (hdr->tc << 9);
    t |= (hdr->rd << 8);
    t |= (hdr->ra << 7);
    t |= hdr->rcode;
    s = htons(t);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    s = htons(hdr->qdcount);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    s = htons(hdr->ancount);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    s = htons(hdr->nscount);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    s = htons(hdr->arcount);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    assert(off == 12);
    return off;
}
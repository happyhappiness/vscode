int
rfc1035QuestionPack(char *buf,
                    const size_t sz,
                    const char *name,
                    const unsigned short type,
                    const unsigned short _class)
{
    unsigned int off = 0;
    unsigned short s;
    off += rfc1035NamePack(buf + off, sz - off, name);
    s = htons(type);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    s = htons(_class);
    memcpy(buf + off, &s, sizeof(s));
    off += sizeof(s);
    assert(off <= sz);
    return off;
}
void
rfc1035SetQueryID(char *buf, unsigned short qid)
{
    unsigned short s = htons(qid);
    memcpy(buf, &s, sizeof(s));
}
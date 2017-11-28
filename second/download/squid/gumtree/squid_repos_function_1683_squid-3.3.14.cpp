int
strListIsMember(const String * list, const char *m, char del)
{
    const char *pos = NULL;
    const char *item;
    int ilen = 0;
    int mlen;

    assert(list && m);
    mlen = strlen(m);
    while (strListGetItem(list, del, &item, &ilen, &pos)) {
        if (mlen == ilen && !strncasecmp(item, m, ilen))
            return 1;
    }
    return 0;
}
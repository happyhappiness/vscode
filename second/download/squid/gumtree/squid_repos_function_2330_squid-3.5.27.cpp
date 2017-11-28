void
NotePairs::addStrList(const char *key, const char *values)
{
    String strValues(values);
    const char *item;
    const char *pos = NULL;
    int ilen = 0;
    while (strListGetItem(&strValues, ',', &item, &ilen, &pos)) {
        String v;
        v.append(item, ilen);
        entries.push_back(new NotePairs::Entry(key, v.termedBuf()));
    }
}
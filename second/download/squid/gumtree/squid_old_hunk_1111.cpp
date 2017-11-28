    /* field stats for all messages */
    storeAppendPrintf(e, "\nHttp Fields Stats (replies and requests)\n");

    storeAppendPrintf(e, "%2s\t %-25s\t %5s\t %6s\t %6s\n",
                      "id", "name", "#alive", "%err", "%repeat");

    for (ht = (http_hdr_type)0; ht < HDR_ENUM_END; ++ht) {
        HttpHeaderFieldInfo *f = Headers + ht;
        storeAppendPrintf(e, "%2d\t %-25s\t %5d\t %6.3f\t %6.3f\n",
                          f->id, f->name.termedBuf(), f->stat.aliveCount,
                          xpercent(f->stat.errCount, f->stat.parsCount),
                          xpercent(f->stat.repCount, f->stat.seenCount));
    }

    storeAppendPrintf(e, "Headers Parsed: %d + %d = %d\n",
                      HttpHeaderStats[hoRequest].parsedCount,
                      HttpHeaderStats[hoReply].parsedCount,
                      HttpHeaderStats[0].parsedCount);
    storeAppendPrintf(e, "Hdr Fields Parsed: %d\n", HeaderEntryParsedCount);
}

http_hdr_type
httpHeaderIdByName(const char *name, size_t name_len, const HttpHeaderFieldInfo * info, int end)
{
    if (name_len > 0) {
        for (int i = 0; i < end; ++i) {
            if (name_len != info[i].name.size())
                continue;

            if (!strncasecmp(name, info[i].name.rawBuf(), name_len))
                return info[i].id;
        }
    }

    return HDR_BAD_HDR;
}

http_hdr_type
httpHeaderIdByNameDef(const char *name, int name_len)
{
    if (!Headers)
        Headers = httpHeaderBuildFieldsInfo(HeadersAttrs, HDR_ENUM_END);

    return httpHeaderIdByName(name, name_len, Headers, HDR_ENUM_END);
}

const char *
httpHeaderNameById(int id)
{
    if (!Headers)
        Headers = httpHeaderBuildFieldsInfo(HeadersAttrs, HDR_ENUM_END);

    assert(id >= 0 && id < HDR_ENUM_END);

    return Headers[id].name.termedBuf();
}

int
HttpHeader::hasListMember(http_hdr_type id, const char *member, const char separator) const
{
    int result = 0;
    const char *pos = NULL;
    const char *item;
    int ilen;
    int mlen = strlen(member);

    assert(id >= 0);

    String header (getStrOrList(id));

    while (strListGetItem(&header, separator, &item, &ilen, &pos)) {
        if (strncasecmp(item, member, mlen) == 0
                && (item[mlen] == '=' || item[mlen] == separator || item[mlen] == ';' || item[mlen] == '\0')) {

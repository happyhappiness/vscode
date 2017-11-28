    /* field stats for all messages */
    storeAppendPrintf(e, "\nHttp Fields Stats (replies and requests)\n");

    storeAppendPrintf(e, "%2s\t %-25s\t %5s\t %6s\t %6s\n",
                      "id", "name", "#alive", "%err", "%repeat");

    // scan heaaderTable and output
    for (auto h : WholeEnum<Http::HdrType>()) {
        auto stats = headerStatsTable[h];
        storeAppendPrintf(e, "%2d\t %-25s\t %5d\t %6.3f\t %6.3f\n",
                          Http::HeaderLookupTable.lookup(h).id,
                          Http::HeaderLookupTable.lookup(h).name,
                          stats.aliveCount,
                          xpercent(stats.errCount, stats.parsCount),
                          xpercent(stats.repCount, stats.seenCount));
    }

    storeAppendPrintf(e, "Headers Parsed: %d + %d = %d\n",
                      HttpHeaderStats[hoRequest].parsedCount,
                      HttpHeaderStats[hoReply].parsedCount,
                      HttpHeaderStats[0].parsedCount);
    storeAppendPrintf(e, "Hdr Fields Parsed: %d\n", HeaderEntryParsedCount);
}

int
HttpHeader::hasListMember(Http::HdrType id, const char *member, const char separator) const
{
    int result = 0;
    const char *pos = NULL;
    const char *item;
    int ilen;
    int mlen = strlen(member);

    assert(any_registered_header(id));

    String header (getStrOrList(id));

    while (strListGetItem(&header, separator, &item, &ilen, &pos)) {
        if (strncasecmp(item, member, mlen) == 0
                && (item[mlen] == '=' || item[mlen] == separator || item[mlen] == ';' || item[mlen] == '\0')) {

void
httpHeaderStoreReport(StoreEntry * e)
{
    int i;
    http_hdr_type ht;
    assert(e);

    HttpHeaderStats[0].parsedCount =
        HttpHeaderStats[hoRequest].parsedCount + HttpHeaderStats[hoReply].parsedCount;
    HttpHeaderStats[0].ccParsedCount =
        HttpHeaderStats[hoRequest].ccParsedCount + HttpHeaderStats[hoReply].ccParsedCount;
    HttpHeaderStats[0].destroyedCount =
        HttpHeaderStats[hoRequest].destroyedCount + HttpHeaderStats[hoReply].destroyedCount;
    HttpHeaderStats[0].busyDestroyedCount =
        HttpHeaderStats[hoRequest].busyDestroyedCount + HttpHeaderStats[hoReply].busyDestroyedCount;

    for (i = 1; i < HttpHeaderStatCount; ++i) {
        httpHeaderStatDump(HttpHeaderStats + i, e);
        storeAppendPrintf(e, "%s\n", "<br>");
    }

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
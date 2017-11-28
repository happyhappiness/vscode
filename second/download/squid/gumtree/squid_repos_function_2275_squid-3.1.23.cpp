static int
CheckQuickAbort2(StoreEntry * entry)
{
    MemObject * const mem = entry->mem_obj;
    assert(mem);
    debugs(90, 3, "CheckQuickAbort2: entry=" << entry << ", mem=" << mem);

    if (mem->request && !mem->request->flags.cachable) {
        debugs(90, 3, "CheckQuickAbort2: YES !mem->request->flags.cachable");
        return 1;
    }

    if (EBIT_TEST(entry->flags, KEY_PRIVATE)) {
        debugs(90, 3, "CheckQuickAbort2: YES KEY_PRIVATE");
        return 1;
    }

    int64_t expectlen = entry->getReply()->content_length + entry->getReply()->hdr_sz;

    if (expectlen < 0)
        /* expectlen is < 0 if *no* information about the object has been received */
        return 1;

    int64_t curlen =  mem->endOffset ();

    if (Config.quickAbort.min < 0) {
        debugs(90, 3, "CheckQuickAbort2: NO disabled");
        return 0;
    }

    if ( Config.rangeOffsetLimit < 0 && mem->request && mem->request->range ) {
        /* Don't abort if the admin has configured range_ofset -1 to download fully for caching. */
        debugs(90, 3, "CheckQuickAbort2: NO admin configured range replies to full-download");
        return 0;
    }

    if (curlen > expectlen) {
        debugs(90, 3, "CheckQuickAbort2: YES bad content length");
        return 1;
    }

    if ((expectlen - curlen) < (Config.quickAbort.min << 10)) {
        debugs(90, 3, "CheckQuickAbort2: NO only little more left");
        return 0;
    }

    if ((expectlen - curlen) > (Config.quickAbort.max << 10)) {
        debugs(90, 3, "CheckQuickAbort2: YES too much left to go");
        return 1;
    }

    if (expectlen < 100) {
        debugs(90, 3, "CheckQuickAbort2: NO avoid FPE");
        return 0;
    }

    if ((curlen / (expectlen / 100)) > (Config.quickAbort.pct)) {
        debugs(90, 3, "CheckQuickAbort2: NO past point of no return");
        return 0;
    }

    debugs(90, 3, "CheckQuickAbort2: YES default, returning 1");
    return 1;
}
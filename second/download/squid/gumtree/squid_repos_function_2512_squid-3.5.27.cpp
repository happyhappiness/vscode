static bool
CheckQuickAbortIsReasonable(StoreEntry * entry)
{
    MemObject * const mem = entry->mem_obj;
    assert(mem);
    debugs(90, 3, "entry=" << entry << ", mem=" << mem);

    if (mem->request && !mem->request->flags.cachable) {
        debugs(90, 3, "quick-abort? YES !mem->request->flags.cachable");
        return true;
    }

    if (EBIT_TEST(entry->flags, KEY_PRIVATE)) {
        debugs(90, 3, "quick-abort? YES KEY_PRIVATE");
        return true;
    }

    int64_t expectlen = entry->getReply()->content_length + entry->getReply()->hdr_sz;

    if (expectlen < 0) {
        /* expectlen is < 0 if *no* information about the object has been received */
        debugs(90, 3, "quick-abort? YES no object data received yet");
        return true;
    }

    int64_t curlen =  mem->endOffset();

    if (Config.quickAbort.min < 0) {
        debugs(90, 3, "quick-abort? NO disabled");
        return false;
    }

    if (mem->request && mem->request->range && mem->request->getRangeOffsetLimit() < 0) {
        /* Don't abort if the admin has configured range_ofset -1 to download fully for caching. */
        debugs(90, 3, "quick-abort? NO admin configured range replies to full-download");
        return false;
    }

    if (curlen > expectlen) {
        debugs(90, 3, "quick-abort? YES bad content length (" << curlen << " of " << expectlen << " bytes received)");
        return true;
    }

    if ((expectlen - curlen) < (Config.quickAbort.min << 10)) {
        debugs(90, 3, "quick-abort? NO only a little more object left to receive");
        return false;
    }

    if ((expectlen - curlen) > (Config.quickAbort.max << 10)) {
        debugs(90, 3, "quick-abort? YES too much left to go");
        return true;
    }

    if (expectlen < 100) {
        debugs(90, 3, "quick-abort? NO avoid FPE");
        return false;
    }

    if ((curlen / (expectlen / 100)) > (Config.quickAbort.pct)) {
        debugs(90, 3, "quick-abort? NO past point of no return");
        return false;
    }

    debugs(90, 3, "quick-abort? YES default");
    return true;
}
void
MemStore::copyToShm(StoreEntry &e)
{
    // prevents remote readers from getting ENTRY_FWD_HDR_WAIT entries and
    // not knowing when the wait is over
    if (EBIT_TEST(e.flags, ENTRY_FWD_HDR_WAIT)) {
        debugs(20, 5, "postponing copying " << e << " for ENTRY_FWD_HDR_WAIT");
        return;
    }

    assert(map);
    assert(e.mem_obj);

    const int64_t eSize = e.mem_obj->endOffset();
    if (e.mem_obj->memCache.offset >= eSize) {
        debugs(20, 5, "postponing copying " << e << " for lack of news: " <<
               e.mem_obj->memCache.offset << " >= " << eSize);
        return; // nothing to do (yet)
    }

    // throw if an accepted unknown-size entry grew too big or max-size changed
    Must(eSize <= maxObjectSize());

    const int32_t index = e.mem_obj->memCache.index;
    assert(index >= 0);
    Ipc::StoreMapAnchor &anchor = map->writeableEntry(index);
    lastWritingSlice = anchor.start;

    // fill, skip slices that are already full
    // Optimize: remember lastWritingSlice in e.mem_obj
    while (e.mem_obj->memCache.offset < eSize) {
        Ipc::StoreMap::Slice &slice = nextAppendableSlice(
                                          e.mem_obj->memCache.index, lastWritingSlice);
        if (anchor.start < 0)
            anchor.start = lastWritingSlice;
        copyToShmSlice(e, anchor, slice);
    }

    debugs(20, 7, "mem-cached available " << eSize << " bytes of " << e);
}
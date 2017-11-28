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

    const int32_t index = e.mem_obj->memCache.index;
    assert(index >= 0);
    Ipc::StoreMapAnchor &anchor = map->writeableEntry(index);

    const int64_t eSize = e.mem_obj->endOffset();
    if (e.mem_obj->memCache.offset >= eSize) {
        debugs(20, 5, "postponing copying " << e << " for lack of news: " <<
               e.mem_obj->memCache.offset << " >= " << eSize);
        return; // nothing to do (yet)
    }

    if (anchor.start < 0) { // must allocate the very first slot for e
        Ipc::Mem::PageId page;
        anchor.start = reserveSapForWriting(page); // throws
        extras->items[anchor.start].page = page;
    }

    lastWritingSlice = anchor.start;
    const size_t sliceCapacity = Ipc::Mem::PageSize();

    // fill, skip slices that are already full
    // Optimize: remember lastWritingSlice in e.mem_obj
    while (e.mem_obj->memCache.offset < eSize) {
        Ipc::StoreMap::Slice &slice =
            map->writeableSlice(e.mem_obj->memCache.index, lastWritingSlice);

        if (slice.size >= sliceCapacity) {
            if (slice.next >= 0) {
                lastWritingSlice = slice.next;
                continue;
            }

            Ipc::Mem::PageId page;
            slice.next = lastWritingSlice = reserveSapForWriting(page);
            extras->items[lastWritingSlice].page = page;
            debugs(20, 7, "entry " << index << " new slice: " << lastWritingSlice);
        }

        copyToShmSlice(e, anchor);
    }

    debugs(20, 7, "mem-cached available " << eSize << " bytes of " << e);
}
bool
MemStore::copyFromShm(StoreEntry &e, const sfileno index, const Ipc::StoreMapAnchor &anchor)
{
    debugs(20, 7, "mem-loading entry " << index << " from " << anchor.start);
    assert(e.mem_obj);

    // emulate the usual Store code but w/o inapplicable checks and callbacks:

    Ipc::StoreMapSliceId sid = anchor.start; // optimize: remember the last sid
    bool wasEof = anchor.complete() && sid < 0;
    int64_t sliceOffset = 0;
    while (sid >= 0) {
        const Ipc::StoreMapSlice &slice = map->readableSlice(index, sid);
        // slice state may change during copying; take snapshots now
        wasEof = anchor.complete() && slice.next < 0;
        const Ipc::StoreMapSlice::Size wasSize = slice.size;

        debugs(20, 9, "entry " << index << " slice " << sid << " eof " <<
               wasEof << " wasSize " << wasSize << " <= " <<
               anchor.basics.swap_file_sz << " sliceOffset " << sliceOffset <<
               " mem.endOffset " << e.mem_obj->endOffset());

        if (e.mem_obj->endOffset() < sliceOffset + wasSize) {
            // size of the slice data that we already copied
            const size_t prefixSize = e.mem_obj->endOffset() - sliceOffset;
            assert(prefixSize <= wasSize);

            const MemStoreMapExtras::Item &extra = extras->items[sid];

            char *page = static_cast<char*>(PagePointer(extra.page));
            const StoreIOBuffer sliceBuf(wasSize - prefixSize,
                                         e.mem_obj->endOffset(),
                                         page + prefixSize);
            if (!copyFromShmSlice(e, sliceBuf, wasEof))
                return false;
            debugs(20, 9, "entry " << index << " copied slice " << sid <<
                   " from " << extra.page << '+' << prefixSize);
        }
        // else skip a [possibly incomplete] slice that we copied earlier

        // careful: the slice may have grown _and_ gotten the next slice ID!
        if (slice.next >= 0) {
            assert(!wasEof);
            // here we know that slice.size may not change any more
            if (wasSize >= slice.size) { // did not grow since we started copying
                sliceOffset += wasSize;
                sid = slice.next;
            }
        } else if (wasSize >= slice.size) { // did not grow
            break;
        }
    }

    if (!wasEof) {
        debugs(20, 7, "mem-loaded " << e.mem_obj->endOffset() << '/' <<
               anchor.basics.swap_file_sz << " bytes of " << e);
        return true;
    }

    debugs(20, 7, "mem-loaded all " << e.mem_obj->object_sz << '/' <<
           anchor.basics.swap_file_sz << " bytes of " << e);

    // from StoreEntry::complete()
    e.mem_obj->object_sz = e.mem_obj->endOffset();
    e.store_status = STORE_OK;
    e.setMemStatus(IN_MEMORY);

    assert(e.mem_obj->object_sz >= 0);
    assert(static_cast<uint64_t>(e.mem_obj->object_sz) == anchor.basics.swap_file_sz);
    // would be nice to call validLength() here, but it needs e.key

    // we read the entire response into the local memory; no more need to lock
    disconnect(e);
    return true;
}
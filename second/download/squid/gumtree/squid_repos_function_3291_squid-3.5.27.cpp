void
MemStore::copyToShmSlice(StoreEntry &e, Ipc::StoreMapAnchor &anchor)
{
    Ipc::StoreMap::Slice &slice =
        map->writeableSlice(e.mem_obj->memCache.index, lastWritingSlice);

    Ipc::Mem::PageId page = extras->items[lastWritingSlice].page;
    assert(lastWritingSlice >= 0 && page);
    debugs(20, 7, "entry " << e << " slice " << lastWritingSlice << " has " <<
           page);

    const int64_t bufSize = Ipc::Mem::PageSize();
    const int64_t sliceOffset = e.mem_obj->memCache.offset % bufSize;
    StoreIOBuffer sharedSpace(bufSize - sliceOffset, e.mem_obj->memCache.offset,
                              static_cast<char*>(PagePointer(page)) + sliceOffset);

    // check that we kept everything or purge incomplete/sparse cached entry
    const ssize_t copied = e.mem_obj->data_hdr.copy(sharedSpace);
    if (copied <= 0) {
        debugs(20, 2, "Failed to mem-cache " << (bufSize - sliceOffset) <<
               " bytes of " << e << " from " << e.mem_obj->memCache.offset <<
               " in " << page);
        throw TexcHere("data_hdr.copy failure");
    }

    debugs(20, 7, "mem-cached " << copied << " bytes of " << e <<
           " from " << e.mem_obj->memCache.offset << " in " << page);

    slice.size += copied;
    e.mem_obj->memCache.offset += copied;
    anchor.basics.swap_file_sz = e.mem_obj->memCache.offset;
}
Ipc::StoreMap::Slice &
MemStore::nextAppendableSlice(const sfileno fileNo, sfileno &sliceOffset)
{
    // allocate the very first slot for the entry if needed
    if (sliceOffset < 0) {
        Ipc::StoreMapAnchor &anchor = map->writeableEntry(fileNo);
        Must(anchor.start < 0);
        Ipc::Mem::PageId page;
        sliceOffset = reserveSapForWriting(page); // throws
        extras->items[sliceOffset].page = page;
        anchor.start = sliceOffset;
    }

    const size_t sliceCapacity = Ipc::Mem::PageSize();
    do {
        Ipc::StoreMap::Slice &slice = map->writeableSlice(fileNo, sliceOffset);

        if (slice.size >= sliceCapacity) {
            if (slice.next >= 0) {
                sliceOffset = slice.next;
                continue;
            }

            Ipc::Mem::PageId page;
            slice.next = sliceOffset = reserveSapForWriting(page);
            extras->items[sliceOffset].page = page;
            debugs(20, 7, "entry " << fileNo << " new slice: " << sliceOffset);
            continue; // to get and return the slice at the new sliceOffset
        }

        return slice;
    } while (true);
    /* not reached */
}
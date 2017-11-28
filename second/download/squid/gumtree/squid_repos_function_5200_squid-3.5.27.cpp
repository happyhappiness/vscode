void
Rock::Rebuild::addSlotToEntry(const sfileno fileno, const SlotId slotId, const DbCellHeader &header)
{
    LoadingEntry &le = entries[fileno];
    Ipc::StoreMapAnchor &anchor = sd->map->writeableEntry(fileno);

    assert(le.version == header.version);

    // mark anchor as loaded or add the secondary slot to the chain
    LoadingEntry &inode = entries[header.firstSlot];
    if (header.firstSlot == slotId) {
        debugs(47,5, "adding inode");
        assert(!inode.freed);
        le.anchored = 1;
    } else {
        debugs(47,9, "linking " << slotId << " to " << inode.more);
        // we do not need to preserve the order
        LoadingEntry &slice = entries[slotId];
        assert(!slice.freed);
        assert(slice.more < 0);
        slice.more = inode.more;
        inode.more = slotId;
    }

    if (header.firstSlot == slotId && !importEntry(anchor, fileno, header)) {
        le.state = LoadingEntry::leCorrupted;
        freeBadEntry(fileno, "corrupted metainfo");
        return;
    }

    // set total entry size and/or check it for consistency
    debugs(47, 8, "header.entrySize: " << header.entrySize << " swap_file_sz: " << anchor.basics.swap_file_sz);
    uint64_t totalSize = header.entrySize;
    assert(totalSize != static_cast<uint64_t>(-1));
    if (!totalSize && anchor.basics.swap_file_sz) {
        assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));
        // perhaps we loaded a later slot (with entrySize) earlier
        totalSize = anchor.basics.swap_file_sz;
    } else if (totalSize && !anchor.basics.swap_file_sz) {
        anchor.basics.swap_file_sz = totalSize;
        assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));
    } else if (totalSize != anchor.basics.swap_file_sz) {
        le.state = LoadingEntry::leCorrupted;
        freeBadEntry(fileno, "size mismatch");
        return;
    }

    le.size += header.payloadSize;

    if (totalSize > 0 && le.size > totalSize) { // overflow
        debugs(47, 8, "overflow: " << le.size << " > " << totalSize);
        le.state = LoadingEntry::leCorrupted;
        freeBadEntry(fileno, "overflowing");
        return;
    }

    mapSlot(slotId, header);
    if (totalSize > 0 && le.size == totalSize) {
        // entry fully loaded, unlock it
        // we have validated that all db cells for this entry were loaded
        EBIT_SET(anchor.basics.flags, ENTRY_VALIDATED);
        le.state = LoadingEntry::leLoaded;
        sd->map->closeForWriting(fileno, false);
        ++counts.objcount;
    }
}
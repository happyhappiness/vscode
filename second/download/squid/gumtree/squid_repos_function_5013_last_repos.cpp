void
Rock::Rebuild::finalizeOrThrow(const sfileno fileNo, LoadingEntry &le)
{
    // walk all map-linked slots, starting from inode, and mark each
    Ipc::StoreMapAnchor &anchor = sd->map->writeableEntry(fileNo);
    Must(le.size > 0); // paranoid
    uint64_t mappedSize = 0;
    SlotId slotId = anchor.start;
    while (slotId >= 0 && mappedSize < le.size) {
        LoadingSlot slot = loadingSlot(slotId); // throws if we have not loaded that slot
        Must(!slot.finalized()); // no loops or stealing from other entries
        Must(slot.mapped()); // all our slots should be in the sd->map
        Must(!slot.freed()); // all our slots should still be present
        slot.finalized(true);

        Ipc::StoreMapSlice &mapSlice = sd->map->writeableSlice(fileNo, slotId);
        Must(mapSlice.size > 0); // paranoid
        mappedSize += mapSlice.size;
        slotId = mapSlice.next;
    }
    /* no hodgepodge entries: one entry - one full chain and no leftovers */
    Must(slotId < 0);
    Must(mappedSize == le.size);

    if (!anchor.basics.swap_file_sz)
        anchor.basics.swap_file_sz = le.size;
    EBIT_SET(anchor.basics.flags, ENTRY_VALIDATED);
    le.state(LoadingEntry::leLoaded);
    sd->map->closeForWriting(fileNo, false);
    ++counts.objcount;
}
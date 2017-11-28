void
Rock::Rebuild::startNewEntry(const sfileno fileno, const SlotId slotId, const DbCellHeader &header)
{
    // If some other from-disk entry is/was using this slot as its inode OR
    // if some other from-disk entry is/was using our inode slot, then the
    // entries are conflicting. We cannot identify other entries, so we just
    // remove ours and hope that the others were/will be handled correctly.
    const LoadingEntry &slice = entries[slotId];
    const LoadingEntry &inode = entries[header.firstSlot];
    if (slice.used() || inode.used()) {
        debugs(47,8, "slice/inode used: " << slice.used() << inode.used());
        LoadingEntry &le = entries[fileno];
        le.state = LoadingEntry::leCorrupted;
        freeSlotIfIdle(slotId, slotId == header.firstSlot);
        // if not idle, the other entry will handle its slice
        ++counts.clashcount;
        return;
    }

    // A miss may have been stored at our fileno while we were loading other
    // slots from disk. We ought to preserve that entry because it is fresher.
    const bool overwriteExisting = false;
    if (Ipc::StoreMap::Anchor *anchor = sd->map->openForWritingAt(fileno, overwriteExisting)) {
        primeNewEntry(*anchor, fileno, header);
        addSlotToEntry(fileno, slotId, header); // may fail
        assert(anchor->basics.swap_file_sz != static_cast<uint64_t>(-1));
    } else {
        // A new from-network entry is occupying our map slot; let it be, but
        // save us from the trouble of going through the above motions again.
        LoadingEntry &le = entries[fileno];
        le.state = LoadingEntry::leIgnored;
        freeSlotIfIdle(slotId, false);
    }
}
void
Rock::Rebuild::startNewEntry(const sfileno fileno, const SlotId slotId, const DbCellHeader &header)
{
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
        LoadingEntry le = loadingEntry(fileno);
        le.state(LoadingEntry::leIgnored);
        freeUnusedSlot(slotId, false);
    }
}
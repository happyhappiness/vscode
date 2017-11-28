void
Rock::Rebuild::freeBadEntry(const sfileno fileno, const char *eDescription)
{
    debugs(47, 2, "cache_dir #" << sd->index << ' ' << eDescription <<
           " entry " << fileno << " is ignored during rebuild");

    LoadingEntry le = loadingEntry(fileno);
    le.state(LoadingEntry::leCorrupted);

    Ipc::StoreMapAnchor &anchor = sd->map->writeableEntry(fileno);
    assert(anchor.start < 0 || le.size > 0);
    for (SlotId slotId = anchor.start; slotId >= 0;) {
        const SlotId next = loadingSlot(slotId).more;
        freeSlot(slotId, true);
        slotId = next;
    }

    sd->map->forgetWritingEntry(fileno);
}
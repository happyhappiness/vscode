void
Rock::Rebuild::freeBadEntry(const sfileno fileno, const char *eDescription)
{
    debugs(47, 2, "cache_dir #" << sd->index << ' ' << eDescription <<
           " entry " << fileno << " is ignored during rebuild");

    Ipc::StoreMapAnchor &anchor = sd->map->writeableEntry(fileno);

    bool freedSome = false;
    // free all loaded non-anchor slots
    SlotId slotId = entries[anchor.start].more;
    while (slotId >= 0) {
        const SlotId next = entries[slotId].more;
        freeSlot(slotId, false);
        slotId = next;
        freedSome = true;
    }
    // free anchor slot if it was loaded
    if (entries[fileno].anchored) {
        freeSlot(anchor.start, false);
        freedSome = true;
    }
    assert(freedSome);

    sd->map->forgetWritingEntry(fileno);
    ++counts.invalid;
}
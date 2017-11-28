void
Rock::Rebuild::useNewSlot(const SlotId slotId, const DbCellHeader &header)
{
    LoadingEntry &slice = entries[slotId];
    assert(!slice.freed); // we cannot free what was not loaded

    const cache_key *const key =
        reinterpret_cast<const cache_key*>(header.key);
    const sfileno fileno = sd->map->anchorIndexByKey(key);
    assert(0 <= fileno && fileno < dbEntryLimit);

    LoadingEntry &le = entries[fileno];
    debugs(47,9, "entry " << fileno << " state: " << le.state << ", inode: " <<
           header.firstSlot << ", size: " << header.payloadSize);

    switch (le.state) {

    case LoadingEntry::leEmpty: {
        startNewEntry(fileno, slotId, header);
        break;
    }

    case LoadingEntry::leLoading: {
        if (canAdd(fileno, slotId, header)) {
            addSlotToEntry(fileno, slotId, header);
        } else {
            // either the loading chain or this slot is stale;
            // be conservative and ignore both (and any future ones)
            le.state = LoadingEntry::leCorrupted;
            freeBadEntry(fileno, "duplicated");
            freeSlotIfIdle(slotId, slotId == header.firstSlot);
            ++counts.dupcount;
        }
        break;
    }

    case LoadingEntry::leLoaded: {
        // either the previously loaded chain or this slot is stale;
        // be conservative and ignore both (and any future ones)
        le.state = LoadingEntry::leCorrupted;
        sd->map->freeEntry(fileno); // may not be immediately successful
        freeSlotIfIdle(slotId, slotId == header.firstSlot);
        ++counts.dupcount;
        break;
    }

    case LoadingEntry::leCorrupted: {
        // previously seen slots messed things up so we must ignore this one
        freeSlotIfIdle(slotId, false);
        break;
    }

    case LoadingEntry::leIgnored: {
        // already replaced by a fresher or colliding from-network entry
        freeSlotIfIdle(slotId, false);
        break;
    }
    }
}
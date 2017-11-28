                   elapsedMsec << "ms; " << (elapsedMsec/validated) << "ms per entry");
            break;
        }
    }
}

/// Either make the entry accessible to all or throw.
/// This method assumes it is called only when no more entry slots are expected.
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

/// Either make the entry accessible to all or free it.
/// This method must only be called when no more entry slots are expected.
void
Rock::Rebuild::finalizeOrFree(const sfileno fileNo, LoadingEntry &le)
{
    try {
        finalizeOrThrow(fileNo, le);
    } catch (const std::exception &ex) {
        freeBadEntry(fileNo, ex.what());
    }
}

void
Rock::Rebuild::validateOneEntry(const sfileno fileNo)
{
    LoadingEntry entry = loadingEntry(fileNo);
    switch (entry.state()) {

    case LoadingEntry::leLoading:
        finalizeOrFree(fileNo, entry);
        break;

    case LoadingEntry::leEmpty: // no entry hashed to this position
    case LoadingEntry::leLoaded: // we have already unlocked this entry
    case LoadingEntry::leCorrupted: // we have already removed this entry
    case LoadingEntry::leIgnored: // we have already discarded this entry
        break;
    }
}

void
Rock::Rebuild::validateOneSlot(const SlotId slotId)
{
    const LoadingSlot slot = loadingSlot(slotId);
    // there should not be any unprocessed slots left
    Must(slot.freed() || (slot.mapped() && slot.finalized()));
}

/// Marks remaining bad entry slots as free and unlocks the entry. The map
/// cannot do this because Loading entries may have holes in the slots chain.
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

void
Rock::Rebuild::swanSong()
{
    debugs(47,3, HERE << "cache_dir #" << sd->index << " rebuild level: " <<

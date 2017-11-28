
/// adds slot to the free slot index
void
Rock::Rebuild::freeSlot(const SlotId slotId, const bool invalid)
{
    debugs(47,5, sd->index << " frees slot " << slotId);
    LoadingSlot slot = loadingSlot(slotId);
    assert(!slot.freed());
    slot.freed(true);

    if (invalid) {
        ++counts.invalid;
        //sd->unlink(fileno); leave garbage on disk, it should not hurt
    }

    Ipc::Mem::PageId pageId;
    pageId.pool = sd->index+1;
    pageId.number = slotId+1;
    sd->freeSlots->push(pageId);
}

/// freeSlot() for never-been-mapped slots
void
Rock::Rebuild::freeUnusedSlot(const SlotId slotId, const bool invalid)
{
    LoadingSlot slot = loadingSlot(slotId);
    // mapped slots must be freed via freeBadEntry() to keep the map in sync
    assert(!slot.mapped());
    freeSlot(slotId, invalid);
}

/// adds slot to the entry chain in the map
void
Rock::Rebuild::mapSlot(const SlotId slotId, const DbCellHeader &header)
{
    LoadingSlot slot = loadingSlot(slotId);
    assert(!slot.mapped());
    assert(!slot.freed());
    slot.mapped(true);

    Ipc::StoreMapSlice slice;
    slice.next = header.nextSlot;
    slice.size = header.payloadSize;
    sd->map->importSlice(slotId, slice);
}

template <class SlotIdType> // accommodates atomic and simple SlotIds.
void
Rock::Rebuild::chainSlots(SlotIdType &from, const SlotId to)
{
    LoadingSlot slot = loadingSlot(to);
    assert(slot.more < 0);
    slot.more = from; // may still be unset
    from = to;
}

/// adds slot to an existing entry chain; caller must check that the slot
/// belongs to the chain it is being added to
void
Rock::Rebuild::addSlotToEntry(const sfileno fileno, const SlotId slotId, const DbCellHeader &header)
{
    LoadingEntry le = loadingEntry(fileno);
    Ipc::StoreMapAnchor &anchor = sd->map->writeableEntry(fileno);

    debugs(47,9, "adding " << slotId << " to entry " << fileno);
    // we do not need to preserve the order
    if (le.anchored()) {
        LoadingSlot inode = loadingSlot(anchor.start);
        chainSlots(inode.more, slotId);
    } else {
        chainSlots(anchor.start, slotId);
    }

    le.size += header.payloadSize; // must precede freeBadEntry() calls

    if (header.firstSlot == slotId) {
        debugs(47,5, "added inode");

        if (le.anchored()) { // we have already added another inode slot
            freeBadEntry(fileno, "inode conflict");
            ++counts.clashcount;
            return;
        }

        le.anchored(true);

        if (!importEntry(anchor, fileno, header)) {
            freeBadEntry(fileno, "corrupted metainfo");
            return;
        }

        // set total entry size and/or check it for consistency
        if (const uint64_t totalSize = header.entrySize) {
            assert(totalSize != static_cast<uint64_t>(-1));
            if (!anchor.basics.swap_file_sz) {
                anchor.basics.swap_file_sz = totalSize;
                assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));
            } else if (totalSize != anchor.basics.swap_file_sz) {
                freeBadEntry(fileno, "size mismatch");
                return;
            }
        }
    }

    const uint64_t totalSize = anchor.basics.swap_file_sz; // may be 0/unknown

    if (totalSize > 0 && le.size > totalSize) { // overflow
        debugs(47, 8, "overflow: " << le.size << " > " << totalSize);
        freeBadEntry(fileno, "overflowing");
        return;
    }

    mapSlot(slotId, header);
    if (totalSize > 0 && le.size == totalSize)
        finalizeOrFree(fileno, le); // entry is probably fully loaded now
}

/// initialize housekeeping information for a newly accepted entry
void
Rock::Rebuild::primeNewEntry(Ipc::StoreMap::Anchor &anchor, const sfileno fileno, const DbCellHeader &header)
{
    anchor.setKey(reinterpret_cast<const cache_key*>(header.key));
    assert(header.firstSlot >= 0);
    anchor.start = -1; // addSlotToEntry() will set it

    assert(anchor.basics.swap_file_sz != static_cast<uint64_t>(-1));

    LoadingEntry le = loadingEntry(fileno);
    le.state(LoadingEntry::leLoading);
    le.version = header.version;
    le.size = 0;
}

/// handle a slot from an entry that we have not seen before
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

/// does the header belong to the fileno entry being loaded?
bool
Rock::Rebuild::sameEntry(const sfileno fileno, const DbCellHeader &header) const
{
    // Header updates always result in multi-start chains and often
    // result in multi-version chains so we can only compare the keys.
    const Ipc::StoreMap::Anchor &anchor = sd->map->writeableEntry(fileno);
    return anchor.sameKey(reinterpret_cast<const cache_key*>(header.key));
}

/// handle freshly loaded (and validated) db slot header
void
Rock::Rebuild::useNewSlot(const SlotId slotId, const DbCellHeader &header)
{
    const cache_key *const key =
        reinterpret_cast<const cache_key*>(header.key);
    const sfileno fileno = sd->map->fileNoByKey(key);
    assert(0 <= fileno && fileno < dbEntryLimit);

    LoadingEntry le = loadingEntry(fileno);
    debugs(47,9, "entry " << fileno << " state: " << le.state() << ", inode: " <<
           header.firstSlot << ", size: " << header.payloadSize);

    switch (le.state()) {

    case LoadingEntry::leEmpty: {
        startNewEntry(fileno, slotId, header);
        break;
    }

    case LoadingEntry::leLoading: {
        if (sameEntry(fileno, header)) {
            addSlotToEntry(fileno, slotId, header); // may fail
        } else {
            // either the loading chain or this slot is stale;
            // be conservative and ignore both (and any future ones)
            freeBadEntry(fileno, "duplicated");
            freeUnusedSlot(slotId, true);
            ++counts.dupcount;
        }
        break;
    }

    case LoadingEntry::leLoaded: {
        // either the previously loaded chain or this slot is stale;
        // be conservative and ignore both (and any future ones)
        le.state(LoadingEntry::leCorrupted);
        sd->map->freeEntry(fileno); // may not be immediately successful
        freeUnusedSlot(slotId, true);
        ++counts.dupcount;
        break;
    }

    case LoadingEntry::leCorrupted: {
        // previously seen slots messed things up so we must ignore this one
        freeUnusedSlot(slotId, true);
        break;
    }

    case LoadingEntry::leIgnored: {
        // already replaced by a fresher or colliding from-network entry
        freeUnusedSlot(slotId, false);
        break;
    }
    }
}


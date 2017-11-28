                   elapsedMsec << "ms; " << (elapsedMsec/validated) << "ms per entry");
            break;
        }
    }
}

void
Rock::Rebuild::validateOneEntry()
{
    LoadingEntry &e = entries[validationPos];
    switch (e.state) {

    case LoadingEntry::leEmpty:
        break; // no entry hashed to this position

    case LoadingEntry::leLoading:
        freeBadEntry(validationPos, "partially stored");
        break;

    case LoadingEntry::leLoaded:
        break; // we have already unlocked this entry

    case LoadingEntry::leCorrupted:
        break; // we have already removed this entry
    }
}

/// Marks remaining bad entry slots as free and unlocks the entry. The map
/// cannot do this because Loading entries may have holes in the slots chain.
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

void
Rock::Rebuild::swanSong()
{
    debugs(47,3, HERE << "cache_dir #" << sd->index << " rebuild level: " <<

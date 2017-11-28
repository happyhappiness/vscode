bool
Ipc::StoreMap::openForUpdating(Update &update, const sfileno fileNoHint)
{
    Must(update.entry);
    const StoreEntry &entry = *update.entry;
    const cache_key *const key = reinterpret_cast<const cache_key*>(entry.key);
    update.stale.name = nameByKey(key);

    if (!validEntry(fileNoHint)) {
        debugs(54, 5, "opening entry with key " << storeKeyText(key) <<
               " for updating " << path);
        update.stale.fileNo = fileNoByName(update.stale.name);
    } else {
        update.stale.fileNo = fileNoHint;
    }

    debugs(54, 5, "opening entry " << update.stale.fileNo << " of " << entry << " for updating " << path);

    // Unreadable entries cannot (e.g., empty and otherwise problematic entries)
    // or should not (e.g., entries still forming their metadata) be updated.
    if (const Anchor *anchor = openForReadingAt(update.stale.fileNo)) {
        if (!anchor->sameKey(key)) {
            closeForReading(update.stale.fileNo);
            debugs(54, 5, "cannot open wrong-key entry " << update.stale.fileNo << " for updating " << path);
            return false;
        }
    } else {
        debugs(54, 5, "cannot open unreadable entry " << update.stale.fileNo << " for updating " << path);
        return false;
    }

    update.stale.anchor = &anchorAt(update.stale.fileNo);
    if (update.stale.anchor->writing()) {
        // TODO: Support updating appending entries.
        // For example, MemStore::updateHeaders() would not know how
        // many old prefix body bytes to copy to the new prefix if the last old
        // prefix slice has not been formed yet (i.e., still gets more bytes).
        debugs(54, 5, "cannot open appending entry " << update.stale.fileNo <<
               " for updating " << path);
        closeForReading(update.stale.fileNo);
        return false;
    }

    if (!update.stale.anchor->lock.lockHeaders()) {
        debugs(54, 5, "cannot open updating entry " << update.stale.fileNo <<
               " for updating " << path);
        closeForReading(update.stale.fileNo);
        return false;
    }

    /* stale anchor is properly locked; we can now use abortUpdating() if needed */

    if (!openKeyless(update.fresh)) {
        debugs(54, 5, "cannot open freshchainless entry " << update.stale.fileNo <<
               " for updating " << path);
        abortUpdating(update);
        return false;
    }

    Must(update.stale);
    Must(update.fresh);
    update.fresh.anchor->set(entry);
    debugs(54, 5, "opened entry " << update.stale.fileNo << " for updating " << path <<
           " using entry " << update.fresh.fileNo << " of " << entry);

    return true;
}
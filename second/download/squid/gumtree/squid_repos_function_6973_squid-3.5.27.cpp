bool
Ipc::StoreMap::purgeOne()
{
    // Hopefully, we find a removable entry much sooner (TODO: use time?).
    // The min() will protect us from division by zero inside the loop.
    const int searchLimit = min(10000, entryLimit());
    int tries = 0;
    for (; tries < searchLimit; ++tries) {
        const sfileno fileno = static_cast<sfileno>(++anchors->victim % entryLimit());
        Anchor &s = anchorAt(fileno);
        if (s.lock.lockExclusive()) {
            // the caller wants a free slice; empty anchor is not enough
            if (!s.empty() && s.start >= 0) {
                // this entry may be marked for deletion, and that is OK
                freeChain(fileno, s, false);
                debugs(54, 5, "purged entry " << fileno << " from " << path);
                return true;
            }
            s.lock.unlockExclusive();
        }
    }
    debugs(54, 5, "no entries to purge from " << path << "; tried: " << tries);
    return false;
}
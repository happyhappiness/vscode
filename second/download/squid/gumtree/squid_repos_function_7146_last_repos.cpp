bool
Ipc::StoreMap::purgeOne()
{
    return visitVictims([&](const sfileno name) {
        const sfileno fileno = fileNoByName(name);
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
        return false;
    });
}
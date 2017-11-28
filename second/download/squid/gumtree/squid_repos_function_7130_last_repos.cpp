void
Ipc::StoreMap::abortWriting(const sfileno fileno)
{
    debugs(54, 5, "aborting entry " << fileno << " for writing " << path);
    Anchor &s = anchorAt(fileno);
    assert(s.writing());
    s.lock.appending = false; // locks out any new readers
    if (!s.lock.readers) {
        freeChain(fileno, s, false);
        debugs(54, 5, "closed clean entry " << fileno << " for writing " << path);
    } else {
        s.waitingToBeFreed = true;
        s.lock.unlockExclusive();
        debugs(54, 5, "closed dirty entry " << fileno << " for writing " << path);
    }
}
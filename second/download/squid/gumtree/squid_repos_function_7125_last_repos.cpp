void
Ipc::StoreMap::closeForWriting(const sfileno fileno, bool lockForReading)
{
    Anchor &s = anchorAt(fileno);
    assert(s.writing());
    if (lockForReading) {
        s.lock.switchExclusiveToShared();
        debugs(54, 5, "switched entry " << fileno <<
               " from writing to reading " << path);
        assert(s.complete());
    } else {
        s.lock.unlockExclusive();
        debugs(54, 5, "closed entry " << fileno << " for writing " << path);
        // cannot assert completeness here because we have no lock
    }
}
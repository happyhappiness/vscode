void
Ipc::StoreMap::closeForReading(const sfileno fileno)
{
    Anchor &s = anchorAt(fileno);
    assert(s.reading());
    s.lock.unlockShared();
    debugs(54, 5, "closed entry " << fileno << " for reading " << path);
}
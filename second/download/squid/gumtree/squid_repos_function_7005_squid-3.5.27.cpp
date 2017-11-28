void
Ipc::MemMap::closeForWriting(const sfileno fileno, bool lockForReading)
{
    debugs(54, 5, "closing slot at " << fileno << " for writing and "
           "openning for reading in map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];
    assert(s.writing());
    if (lockForReading)
        s.lock.switchExclusiveToShared();
    else
        s.lock.unlockExclusive();
}
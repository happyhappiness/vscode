void
Ipc::MemMap::closeForReading(const sfileno fileno)
{
    debugs(54, 5, "closing slot at " << fileno << " for reading in "
           "map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];
    assert(s.reading());
    s.lock.unlockShared();
}
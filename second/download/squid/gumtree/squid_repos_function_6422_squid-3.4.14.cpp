void
Ipc::StoreMap::closeForWriting(const sfileno fileno, bool lockForReading)
{
    debugs(54, 5, HERE << " closing slot at " << fileno << " for writing and "
           "openning for reading in map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];
    assert(s.state == Slot::Writeable);
    s.state = Slot::Readable;
    if (lockForReading)
        s.lock.switchExclusiveToShared();
    else
        s.lock.unlockExclusive();
}
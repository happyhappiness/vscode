void
Ipc::StoreMap::closeForReading(const sfileno fileno)
{
    debugs(54, 5, HERE << " closing slot at " << fileno << " for reading in "
           "map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];
    assert(s.state == Slot::Readable);
    s.lock.unlockShared();
}
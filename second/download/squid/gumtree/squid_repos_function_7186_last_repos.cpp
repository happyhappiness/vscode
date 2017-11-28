const Ipc::MemMap::Slot *
Ipc::MemMap::openForReadingAt(const sfileno fileno)
{
    debugs(54, 5, "trying to open slot at " << fileno << " for "
           "reading in map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];

    if (!s.lock.lockShared()) {
        debugs(54, 5, "failed to lock slot at " << fileno << " for "
               "reading in map [" << path << ']');
        return NULL;
    }

    if (s.empty()) {
        s.lock.unlockShared();
        debugs(54, 7, "empty slot at " << fileno << " for "
               "reading in map [" << path << ']');
        return NULL;
    }

    if (s.waitingToBeFreed) {
        s.lock.unlockShared();
        debugs(54, 7, "dirty slot at " << fileno << " for "
               "reading in map [" << path << ']');
        return NULL;
    }

    debugs(54, 5, "opened slot at " << fileno << " for reading in"
           " map [" << path << ']');
    return &s;
}
const Ipc::StoreMap::Slot *
Ipc::StoreMap::openForReadingAt(const sfileno fileno)
{
    debugs(54, 5, HERE << " trying to open slot at " << fileno << " for "
           "reading in map [" << path << ']');
    assert(valid(fileno));
    Slot &s = shared->slots[fileno];

    if (!s.lock.lockShared()) {
        debugs(54, 5, HERE << " failed to lock slot at " << fileno << " for "
               "reading in map [" << path << ']');
        return NULL;
    }

    if (s.state == Slot::Empty) {
        s.lock.unlockShared();
        debugs(54, 7, HERE << " empty slot at " << fileno << " for "
               "reading in map [" << path << ']');
        return NULL;
    }

    if (s.waitingToBeFreed) {
        s.lock.unlockShared();
        debugs(54, 7, HERE << " dirty slot at " << fileno << " for "
               "reading in map [" << path << ']');
        return NULL;
    }

    // cannot be Writing here if we got shared lock and checked Empty above
    assert(s.state == Slot::Readable);
    debugs(54, 5, HERE << " opened slot at " << fileno << " for reading in"
           " map [" << path << ']');
    return &s;
}
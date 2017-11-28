Ipc::StoreMap::Slot *
Ipc::StoreMap::openForWriting(const cache_key *const key, sfileno &fileno)
{
    debugs(54, 5, HERE << " trying to open slot for key " << storeKeyText(key)
           << " for writing in map [" << path << ']');
    const int idx = slotIndexByKey(key);

    Slot &s = shared->slots[idx];
    ReadWriteLock &lock = s.lock;

    if (lock.lockExclusive()) {
        assert(s.state != Slot::Writeable); // until we start breaking locks

        // free if the entry was used, keeping the entry locked
        if (s.waitingToBeFreed || s.state == Slot::Readable)
            freeLocked(s, true);

        assert(s.state == Slot::Empty);
        ++shared->count;
        s.state = Slot::Writeable;
        fileno = idx;
        //s.setKey(key); // XXX: the caller should do that
        debugs(54, 5, HERE << " opened slot at " << idx <<
               " for writing in map [" << path << ']');
        return &s; // and keep the entry locked
    }

    debugs(54, 5, HERE << " failed to open slot at " << idx <<
           " for writing in map [" << path << ']');
    return NULL;
}
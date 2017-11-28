Ipc::MemMap::Slot *
Ipc::MemMap::openForWritingAt(const sfileno fileno, bool overwriteExisting)
{
    Slot &s = shared->slots[fileno];
    ReadWriteLock &lock = s.lock;

    if (lock.lockExclusive()) {
        assert(s.writing() && !s.reading());

        // bail if we cannot empty this position
        if (!s.waitingToBeFreed && !s.empty() && !overwriteExisting) {
            lock.unlockExclusive();
            debugs(54, 5, "cannot open existing entry " << fileno <<
                   " for writing " << path);
            return NULL;
        }

        // free if the entry was used, keeping the entry locked
        if (s.waitingToBeFreed || !s.empty())
            freeLocked(s, true);

        assert(s.empty());
        ++shared->count;

        debugs(54, 5, "opened slot at " << fileno <<
               " for writing in map [" << path << ']');
        return &s; // and keep the entry locked
    }

    debugs(54, 5, "failed to open slot at " << fileno <<
           " for writing in map [" << path << ']');
    return NULL;
}
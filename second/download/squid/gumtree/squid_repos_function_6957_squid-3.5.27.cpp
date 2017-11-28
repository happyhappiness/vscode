Ipc::StoreMap::Anchor *
Ipc::StoreMap::openForWritingAt(const sfileno fileno, bool overwriteExisting)
{
    Anchor &s = anchorAt(fileno);
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
            freeChain(fileno, s, true);

        assert(s.empty());
        s.start = -1; // we have not allocated any slices yet
        ++anchors->count;

        //s.setKey(key); // XXX: the caller should do that
        debugs(54, 5, "opened entry " << fileno << " for writing " << path);
        return &s; // and keep the entry locked
    }

    debugs(54, 5, "cannot open busy entry " << fileno <<
           " for writing " << path);
    return NULL;
}
void
Ipc::StoreMap::freeLocked(Slot &s, bool keepLocked)
{
    if (s.state == Slot::Readable && cleaner)
        cleaner->cleanReadable(&s - shared->slots.raw());

    s.waitingToBeFreed = false;
    s.state = Slot::Empty;
    if (!keepLocked)
        s.lock.unlockExclusive();
    --shared->count;
    debugs(54, 5, HERE << " freed slot at " << (&s - shared->slots.raw()) <<
           " in map [" << path << ']');
}
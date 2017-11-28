void
Ipc::MemMap::freeLocked(Slot &s, bool keepLocked)
{
    if (!s.empty() && cleaner)
        cleaner->noteFreeMapSlot(&s - shared->slots.raw());

    s.waitingToBeFreed = false;
    memset(s.key, 0, sizeof(s.key));
    if (!keepLocked)
        s.lock.unlockExclusive();
    --shared->count;
    debugs(54, 5, "freed slot at " << (&s - shared->slots.raw()) <<
           " in map [" << path << ']');
}
void
Ipc::StoreMap::free(const sfileno fileno)
{
    debugs(54, 5, HERE << " marking slot at " << fileno << " to be freed in"
           " map [" << path << ']');

    assert(valid(fileno));
    Slot &s = shared->slots[fileno];

    if (s.lock.lockExclusive())
        freeLocked(s, false);
    else
        s.waitingToBeFreed = true; // mark to free it later
}
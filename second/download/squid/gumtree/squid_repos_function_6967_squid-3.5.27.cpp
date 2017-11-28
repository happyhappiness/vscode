void
Ipc::StoreMap::freeEntry(const sfileno fileno)
{
    debugs(54, 5, "marking entry " << fileno << " to be freed in " << path);

    Anchor &s = anchorAt(fileno);

    if (s.lock.lockExclusive())
        freeChain(fileno, s, false);
    else
        s.waitingToBeFreed = true; // mark to free it later
}
void
Ipc::StoreMap::freeChain(const sfileno fileno, Anchor &inode, const bool keepLocked)
{
    debugs(54, 7, "freeing entry " << fileno <<
           " in " << path);
    if (!inode.empty())
        freeChainAt(inode.start, inode.splicingPoint);
    inode.rewind();

    if (!keepLocked)
        inode.lock.unlockExclusive();
    --anchors->count;
    debugs(54, 5, "freed entry " << fileno << " in " << path);
}
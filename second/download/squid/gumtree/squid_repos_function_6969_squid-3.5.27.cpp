void
Ipc::StoreMap::freeChain(const sfileno fileno, Anchor &inode, const bool keepLocked)
{
    debugs(54, 7, "freeing entry " << fileno <<
           " in " << path);
    if (!inode.empty()) {
        sfileno sliceId = inode.start;
        debugs(54, 8, "first slice " << sliceId);
        while (sliceId >= 0) {
            Slice &slice = sliceAt(sliceId);
            const sfileno nextId = slice.next;
            slice.size = 0;
            slice.next = -1;
            if (cleaner)
                cleaner->noteFreeMapSlice(sliceId); // might change slice state
            sliceId = nextId;
        }
    }

    inode.waitingToBeFreed = false;
    inode.rewind();

    if (!keepLocked)
        inode.lock.unlockExclusive();
    --anchors->count;
    debugs(54, 5, "freed entry " << fileno << " in " << path);
}
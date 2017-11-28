void
Ipc::StoreMap::freeChainAt(SliceId sliceId, const SliceId splicingPoint)
{
    static uint64_t ChainId = 0; // to pair freeing/freed calls in debugs()
    const uint64_t chainId = ++ChainId;
    debugs(54, 7, "freeing chain #" << chainId << " starting at " << sliceId << " in " << path);
    while (sliceId >= 0) {
        Slice &slice = sliceAt(sliceId);
        const SliceId nextId = slice.next;
        slice.size = 0;
        slice.next = -1;
        if (cleaner)
            cleaner->noteFreeMapSlice(sliceId); // might change slice state
        if (sliceId == splicingPoint) {
            debugs(54, 5, "preserving chain #" << chainId << " in " << path <<
                   " suffix after slice " << splicingPoint);
            break; // do not free the rest of the chain
        }
        sliceId = nextId;
    }
    debugs(54, 7, "freed chain #" << chainId << " in " << path);
}
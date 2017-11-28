Ipc::StoreMap::SliceId
Ipc::StoreMap::sliceContaining(const sfileno fileno, const uint64_t bytesNeeded) const
{
    const Anchor &anchor = anchorAt(fileno);
    Must(anchor.reading());
    uint64_t bytesSeen = 0;
    SliceId lastSlice = anchor.start;
    while (lastSlice >= 0) {
        const Slice &slice = sliceAt(lastSlice);
        bytesSeen += slice.size;
        if (bytesSeen >= bytesNeeded)
            break;
        lastSlice = slice.next;
    }
    debugs(54, 7, "entry " << fileno << " has " << bytesNeeded << '/' << bytesSeen <<
           " bytes at slice " << lastSlice << " in " << path);
    return lastSlice; // may be negative
}
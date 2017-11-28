void
Ipc::StoreMap::importSlice(const SliceId sliceId, const Slice &slice)
{
    // Slices are imported into positions that should not be available via
    // "get free slice" API. This is not something we can double check
    // reliably because the anchor for the imported slice may not have been
    // imported yet.
    assert(validSlice(sliceId));
    sliceAt(sliceId) = slice;
}
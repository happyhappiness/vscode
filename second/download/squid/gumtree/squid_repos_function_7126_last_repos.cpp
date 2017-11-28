Ipc::StoreMap::Slice &
Ipc::StoreMap::writeableSlice(const AnchorId anchorId, const SliceId sliceId)
{
    assert(anchorAt(anchorId).writing());
    assert(validSlice(sliceId));
    return sliceAt(sliceId);
}
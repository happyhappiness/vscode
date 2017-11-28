const Ipc::StoreMap::Slice &
Ipc::StoreMap::readableSlice(const AnchorId anchorId, const SliceId sliceId) const
{
    assert(anchorAt(anchorId).reading());
    assert(validSlice(sliceId));
    return sliceAt(sliceId);
}
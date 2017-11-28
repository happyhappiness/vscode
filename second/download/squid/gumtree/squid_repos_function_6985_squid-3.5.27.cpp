Ipc::StoreMap::Slice&
Ipc::StoreMap::sliceAt(const SliceId sliceId)
{
    assert(validSlice(sliceId));
    return slices->items[sliceId];
}
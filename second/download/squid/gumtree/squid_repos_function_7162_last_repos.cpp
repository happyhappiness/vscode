const Ipc::StoreMap::Slice&
Ipc::StoreMap::sliceAt(const SliceId sliceId) const
{
    return const_cast<StoreMap&>(*this).sliceAt(sliceId);
}
size_t
Ipc::StoreMap::Shared::sharedMemorySize() const
{
    return SharedMemorySize(limit, extrasSize);
}
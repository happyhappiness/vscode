size_t
Ipc::MemMap::Shared::sharedMemorySize() const
{
    return SharedMemorySize(limit, extrasSize);
}
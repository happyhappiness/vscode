size_t
Ipc::StoreMap::Shared::SharedMemorySize(const int limit, const size_t extrasSize)
{
    return sizeof(Shared) + limit * (sizeof(Slot) + extrasSize);
}
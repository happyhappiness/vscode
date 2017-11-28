Ipc::Mem::PagePool::Owner *
Ipc::Mem::PagePool::Init(const char *const id, const unsigned int capacity, const size_t pageSize)
{
    static uint32_t LastPagePoolId = 0;
    if (++LastPagePoolId == 0)
        ++LastPagePoolId; // skip zero pool id
    return shm_new(PageStack)(id, LastPagePoolId, capacity, pageSize);
}
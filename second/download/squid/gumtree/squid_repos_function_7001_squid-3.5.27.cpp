Ipc::MemMap::Owner *
Ipc::MemMap::Init(const char *const path, const int limit, const size_t extrasSize)
{
    assert(limit > 0); // we should not be created otherwise
    Owner *const owner = shm_new(Shared)(path, limit, extrasSize);
    debugs(54, 5, "new map [" << path << "] created: " << limit);
    return owner;
}
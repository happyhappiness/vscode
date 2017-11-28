Ipc::MemMap::Owner *
Ipc::MemMap::Init(const char *const path, const int limit)
{
    return Init(path, limit, 0);
}
size_t
Ipc::Mem::PageLevel(const int purpose)
{
    return ThePagePool ? ThePagePool->level(purpose) : 0;
}
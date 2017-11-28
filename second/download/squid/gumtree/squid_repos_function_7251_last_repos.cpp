size_t
Ipc::Mem::PageLevel()
{
    return ThePagePool ? ThePagePool->level() : 0;
}
void
DelayPool::freeData()
{
    delete pool;
    pool = NULL;
}
MemPoolIterator *
memPoolIterate(void)
{
    Iterator.pool = MemPools::GetInstance().pools;
    return &Iterator;
}
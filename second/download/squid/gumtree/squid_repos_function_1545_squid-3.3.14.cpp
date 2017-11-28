void *
CommonPool::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (CommonPool);
    return ::operator new (size);
}
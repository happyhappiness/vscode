void *
ClassCNetPool::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (ClassCNetPool);
    return ::operator new (size);
}
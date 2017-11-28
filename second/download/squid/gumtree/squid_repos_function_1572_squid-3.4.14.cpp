void *
Aggregate::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (Aggregate);
    return ::operator new (size);
}
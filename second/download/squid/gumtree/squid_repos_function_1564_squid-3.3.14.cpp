void *
Aggregate::AggregateId::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (AggregateId);
    return ::operator new (size);
}
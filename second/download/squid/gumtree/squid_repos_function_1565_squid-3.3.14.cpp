void
Aggregate::AggregateId::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (AggregateId);
    ::operator delete (address);
}
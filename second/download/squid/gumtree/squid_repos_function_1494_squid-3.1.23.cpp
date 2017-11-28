void
Aggregate::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (Aggregate);
    ::operator delete (address);
}
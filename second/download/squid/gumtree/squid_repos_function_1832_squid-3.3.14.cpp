void
NullDelayId::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (NullDelayId);
    ::operator delete (address);
}
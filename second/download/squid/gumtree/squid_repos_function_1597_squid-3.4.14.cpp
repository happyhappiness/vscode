void
IndividualPool::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (IndividualPool);
    ::operator delete (address);
}
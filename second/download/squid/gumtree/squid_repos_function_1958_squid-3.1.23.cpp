void
DelayTaggedBucket::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (DelayTaggedBucket);
    ::operator delete (address);
}
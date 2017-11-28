void
DelayUserBucket::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (DelayUserBucket);
    ::operator delete (address);
}
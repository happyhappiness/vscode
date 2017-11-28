void *
DelayUserBucket::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (DelayUserBucket);
    return ::operator new (size);
}
void *
DelayTaggedBucket::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (DelayTaggedBucket);
    return ::operator new (size);
}
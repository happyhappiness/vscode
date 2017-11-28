void *
IndividualPool::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (IndividualPool);
    return ::operator new (size);
}
void *
NullDelayId::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (NullDelayId);
    return ::operator new (size);
}
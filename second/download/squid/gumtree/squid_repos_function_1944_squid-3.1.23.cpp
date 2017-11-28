void *
DelayTagged::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (DelayTagged);
    return ::operator new (size);
}
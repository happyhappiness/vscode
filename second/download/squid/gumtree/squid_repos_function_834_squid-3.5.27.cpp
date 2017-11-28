void *
DelayVector::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (DelayVector);
    return ::operator new (size);
}
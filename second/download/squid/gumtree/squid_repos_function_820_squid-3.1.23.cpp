void *
DelayVector::Id::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (Id);
    return ::operator new (size);
}
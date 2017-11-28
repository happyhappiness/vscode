void *
DelayUser::operator new(size_t size)
{
    DelayPools::MemoryUsed += sizeof (DelayUser);
    return ::operator new (size);
}
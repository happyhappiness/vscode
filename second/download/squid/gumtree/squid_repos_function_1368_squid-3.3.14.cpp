void
DelayUser::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (DelayUser);
    ::operator delete (address);
}
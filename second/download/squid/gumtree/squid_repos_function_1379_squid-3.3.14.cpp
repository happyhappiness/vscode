void
DelayUser::Id::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (Id);
    ::operator delete (address);
}
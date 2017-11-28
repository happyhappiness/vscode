void
DelayTagged::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (DelayTagged);
    ::operator delete (address);
}
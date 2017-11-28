void
ClassCNetPool::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (ClassCNetPool);
    ::operator delete (address);
}
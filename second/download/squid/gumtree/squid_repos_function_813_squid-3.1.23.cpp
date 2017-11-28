void
DelayVector::operator delete (void *address)
{
    DelayPools::MemoryUsed -= sizeof (DelayVector);
    ::operator delete (address);
}
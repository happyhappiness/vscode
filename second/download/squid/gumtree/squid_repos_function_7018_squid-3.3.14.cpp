_SQUID_EXTERNNEW_ void operator delete[] (void *address) throw()
{
    xfree(address);
}
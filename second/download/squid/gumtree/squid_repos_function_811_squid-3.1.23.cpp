void operator delete[] (void *address) throw()
{
    xfree (address);
}
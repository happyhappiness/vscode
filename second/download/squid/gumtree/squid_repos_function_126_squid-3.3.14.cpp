void
BaseVirtual::operator delete(void *address)
{
    Calls.recordDelete();
    ::operator delete (address);
}
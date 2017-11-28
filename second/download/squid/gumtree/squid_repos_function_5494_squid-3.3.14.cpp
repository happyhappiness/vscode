template <class RT>
void
IoResult<RT>::operator delete(void *address)
{
    cbdataFree(address);
}
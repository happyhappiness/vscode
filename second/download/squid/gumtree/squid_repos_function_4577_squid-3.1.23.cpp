void
CossRead::operator delete (void *address)
{
    cbdataFree(address);
}
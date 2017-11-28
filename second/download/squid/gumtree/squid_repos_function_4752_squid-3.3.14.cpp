void
CossWrite::operator delete (void *address)
{
    cbdataFree(address);
}
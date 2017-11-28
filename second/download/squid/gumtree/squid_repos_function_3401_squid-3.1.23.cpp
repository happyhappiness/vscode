void
ClientSocketContext::operator delete (void *address)
{
    cbdataFree (address);
}
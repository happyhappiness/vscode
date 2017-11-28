void
ConnectStateData::operator delete (void *address)
{
    cbdataFree(address);
}
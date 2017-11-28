void
esiRemove::operator delete (void *address)
{
    cbdataFree (address);
}
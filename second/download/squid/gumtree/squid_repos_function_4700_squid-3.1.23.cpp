void
UFSStoreState::operator delete (void *address)
{
    cbdataFree(address);
}
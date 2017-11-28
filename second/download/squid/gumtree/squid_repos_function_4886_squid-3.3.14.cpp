void
Fs::Ufs::UFSStoreState::operator delete (void *address)
{
    cbdataFree(address);
}
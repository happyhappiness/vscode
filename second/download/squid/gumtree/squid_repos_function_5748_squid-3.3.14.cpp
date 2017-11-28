void
AIODiskFile::operator delete(void *address)
{
    cbdataFree(address);
}
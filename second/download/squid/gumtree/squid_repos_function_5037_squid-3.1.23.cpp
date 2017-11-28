void
DiskThreadsDiskFile::operator delete(void *address)
{
    DiskThreadsDiskFile *t = static_cast<DiskThreadsDiskFile *>(address);
    cbdataFree(t);
}
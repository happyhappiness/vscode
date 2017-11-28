void
MmappedFile::operator delete(void *address)
{
    MmappedFile *t = static_cast<MmappedFile *>(address);
    cbdataFree(t);
}
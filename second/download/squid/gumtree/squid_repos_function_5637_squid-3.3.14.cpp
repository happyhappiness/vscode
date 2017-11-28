void
DiskdFile::operator delete(void *address)
{
    DiskdFile *t = static_cast<DiskdFile *>(address);
    debugs(79, 3, "diskdFile with base " << t << " deleting");
    cbdataFree(t);
}
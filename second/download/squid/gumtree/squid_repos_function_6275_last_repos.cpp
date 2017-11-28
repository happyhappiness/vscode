void
DiskThreadsDiskFile::OpenDone(int fd, void *cbdata, const char *buf, int aio_return, int aio_errno)
{
    DiskThreadsDiskFile *myFile = static_cast<DiskThreadsDiskFile *>(cbdata);
    myFile->openDone (fd, buf, aio_return, aio_errno);
}
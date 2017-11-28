bool
DiskThreadsDiskFile::canRead() const
{
    debugs(79, 3, "DiskThreadsDiskFile::canRead: fd is " << fd);
    return fd > -1;
}
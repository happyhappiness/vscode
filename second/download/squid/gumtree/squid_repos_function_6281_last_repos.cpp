bool
DiskThreadsDiskFile::canWrite() const
{
    return fd > -1;
}
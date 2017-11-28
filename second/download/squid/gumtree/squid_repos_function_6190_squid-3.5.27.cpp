bool
MmappedFile::canWrite() const
{
    return fd >= 0;
}
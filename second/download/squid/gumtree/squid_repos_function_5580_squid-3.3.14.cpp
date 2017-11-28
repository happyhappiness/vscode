bool
MmappedFile::canRead() const
{
    return fd >= 0;
}
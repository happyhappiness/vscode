DiskFile::Pointer
MmappedIOStrategy::newFile (char const *path)
{
    return new MmappedFile (path);
}
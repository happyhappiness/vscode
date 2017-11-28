DiskFile::Pointer
DiskThreadsIOStrategy::newFile (char const *path)
{
    if (shedLoad()) {
        return NULL;
    }

    return new DiskThreadsDiskFile (path, this);
}
RefCount<DiskFile>
AIODiskIOStrategy::newFile (char const *path)
{
    if (shedLoad()) {
        return NULL;
    }

    return new AIODiskFile (path, this);
}
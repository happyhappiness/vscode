DiskFile::Pointer
DiskdIOStrategy::newFile(char const *path)
{
    if (shedLoad()) {
        openFailed();
        return NULL;
    }

    return new DiskdFile (path, this);
}
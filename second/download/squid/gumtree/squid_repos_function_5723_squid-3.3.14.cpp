DiskFile::Pointer
BlockingIOStrategy::newFile (char const *path)
{
    return new BlockingFile (path);
}
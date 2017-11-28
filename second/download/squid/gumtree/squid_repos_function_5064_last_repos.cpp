DiskFile::Pointer
Fs::Ufs::UFSStrategy::newFile (char const *path)
{
    return io->newFile(path);
}
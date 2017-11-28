void
DiskThreadsIOStrategy::unlinkFile(char const *path)
{
    ++statCounter.syscalls.disk.unlinks;
    aioUnlink(path, NULL, NULL);
}
int
storeDirGetBlkSize(const char *path, int *blksize)
{
    struct statvfs sfs;

    if (xstatvfs(path, &sfs)) {
        debugs(50, DBG_IMPORTANT, "" << path << ": " << xstrerror());
        *blksize = 2048;
        return 1;
    }

    *blksize = (int) sfs.f_frsize;

    // Sanity check; make sure we have a meaningful value.
    if (*blksize < 512)
        *blksize = 2048;

    return 0;
}
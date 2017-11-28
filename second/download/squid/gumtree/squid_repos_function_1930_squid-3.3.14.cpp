int
storeDirGetBlkSize(const char *path, int *blksize)
{
#if HAVE_STATVFS

    struct statvfs sfs;

    if (statvfs(path, &sfs)) {
        debugs(50, DBG_IMPORTANT, "" << path << ": " << xstrerror());
        *blksize = 2048;
        return 1;
    }

    *blksize = (int) sfs.f_frsize;
#else

    struct statfs sfs;

    if (statfs(path, &sfs)) {
        debugs(50, DBG_IMPORTANT, "" << path << ": " << xstrerror());
        *blksize = 2048;
        return 1;
    }

    *blksize = (int) sfs.f_bsize;
#endif
    /*
     * Sanity check; make sure we have a meaningful value.
     */

    if (*blksize < 512)
        *blksize = 2048;

    return 0;
}
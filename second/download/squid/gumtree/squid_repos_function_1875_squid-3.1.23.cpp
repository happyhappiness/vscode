int
storeDirGetUFSStats(const char *path, int *totl_kb, int *free_kb, int *totl_in, int *free_in)
{
#if HAVE_STATVFS

    struct statvfs sfs;

    if (statvfs(path, &sfs)) {
        debugs(50, 1, "" << path << ": " << xstrerror());
        return 1;
    }

    *totl_kb = (int) fsbtoblk(sfs.f_blocks, sfs.f_frsize, 1024);
    *free_kb = (int) fsbtoblk(sfs.f_bfree, sfs.f_frsize, 1024);
    *totl_in = (int) sfs.f_files;
    *free_in = (int) sfs.f_ffree;
#else

    struct statfs sfs;

    if (statfs(path, &sfs)) {
        debugs(50, 1, "" << path << ": " << xstrerror());
        return 1;
    }

    *totl_kb = (int) fsbtoblk(sfs.f_blocks, sfs.f_bsize, 1024);
    *free_kb = (int) fsbtoblk(sfs.f_bfree, sfs.f_bsize, 1024);
    *totl_in = (int) sfs.f_files;
    *free_in = (int) sfs.f_ffree;
#endif

    return 0;
}
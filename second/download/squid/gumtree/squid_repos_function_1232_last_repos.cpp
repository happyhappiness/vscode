int
fsStats(const char *path, int *totl_kb, int *free_kb, int *totl_in, int *free_in)
{
    struct statvfs sfs;

    if (xstatvfs(path, &sfs)) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, "" << path << ": " << xstrerr(xerrno));
        return 1;
    }

    *totl_kb = (int) fsbtoblk(sfs.f_blocks, sfs.f_frsize, 1024);
    *free_kb = (int) fsbtoblk(sfs.f_bfree, sfs.f_frsize, 1024);
    *totl_in = (int) sfs.f_files;
    *free_in = (int) sfs.f_ffree;
    return 0;
}
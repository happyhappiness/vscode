int
statfs(const char *path, struct statfs *sfs)
{
    char drive[4];
    DWORD spc, bps, freec, totalc;
    DWORD vsn, maxlen, flags;

    if (!sfs) {
        errno = EINVAL;
        return -1;
    }
    strncpy(drive, path, 2);
    drive[2] = '\0';
    strcat(drive, "\\");

    if (!GetDiskFreeSpace(drive, &spc, &bps, &freec, &totalc)) {
        errno = ENOENT;
        return -1;
    }
    if (!GetVolumeInformation(drive, NULL, 0, &vsn, &maxlen, &flags, NULL, 0)) {
        errno = ENOENT;
        return -1;
    }
    sfs->f_type = flags;
    sfs->f_bsize = spc * bps;
    sfs->f_blocks = totalc;
    sfs->f_bfree = sfs->f_bavail = freec;
    sfs->f_files = -1;
    sfs->f_ffree = -1;
    sfs->f_fsid = vsn;
    sfs->f_namelen = maxlen;
    return 0;
}
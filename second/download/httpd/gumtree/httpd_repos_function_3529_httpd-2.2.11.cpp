mode_t apr_unix_perms2mode(apr_fileperms_t perms)
{
    mode_t mode = 0;

    if (perms & APR_USETID)
        mode |= S_ISUID;
    if (perms & APR_UREAD)
        mode |= S_IRUSR;
    if (perms & APR_UWRITE)
        mode |= S_IWUSR;
    if (perms & APR_UEXECUTE)
        mode |= S_IXUSR;

    if (perms & APR_GSETID)
        mode |= S_ISGID;
    if (perms & APR_GREAD)
        mode |= S_IRGRP;
    if (perms & APR_GWRITE)
        mode |= S_IWGRP;
    if (perms & APR_GEXECUTE)
        mode |= S_IXGRP;

#ifdef S_ISVTX
    if (perms & APR_WSTICKY)
        mode |= S_ISVTX;
#endif
    if (perms & APR_WREAD)
        mode |= S_IROTH;
    if (perms & APR_WWRITE)
        mode |= S_IWOTH;
    if (perms & APR_WEXECUTE)
        mode |= S_IXOTH;

    return mode;
}
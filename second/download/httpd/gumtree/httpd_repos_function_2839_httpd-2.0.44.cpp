apr_fileperms_t apr_unix_mode2perms(mode_t mode)
{
    apr_fileperms_t perms = 0;

    if (mode & S_IRUSR)
        perms |= APR_UREAD;
    if (mode & S_IWUSR)
        perms |= APR_UWRITE;
    if (mode & S_IXUSR)
        perms |= APR_UEXECUTE;

    if (mode & S_IRGRP)
        perms |= APR_GREAD;
    if (mode & S_IWGRP)
        perms |= APR_GWRITE;
    if (mode & S_IXGRP)
        perms |= APR_GEXECUTE;

    if (mode & S_IROTH)
        perms |= APR_WREAD;
    if (mode & S_IWOTH)
        perms |= APR_WWRITE;
    if (mode & S_IXOTH)
        perms |= APR_WEXECUTE;

    return perms;
}
apr_status_t filepath_drive_get(char **rootpath, char drive, 
                                apr_int32_t flags, apr_pool_t *p)
{
    char path[APR_PATH_MAX];
    char *pos;
    ULONG rc;
    ULONG bufsize = sizeof(path) - 3;

    path[0] = drive;
    path[1] = ':';
    path[2] = '/';

    rc = DosQueryCurrentDir(apr_toupper(drive) - 'A', path+3, &bufsize);

    if (rc) {
        return APR_FROM_OS_ERROR(rc);
    }

    if (!(flags & APR_FILEPATH_NATIVE)) {
        for (pos=path; *pos; pos++) {
            if (*pos == '\\')
                *pos = '/';
        }
    }

    *rootpath = apr_pstrdup(p, path);
    return APR_SUCCESS;
}
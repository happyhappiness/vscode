DIR *
opendir(const CHAR * szPath)
{
    DIR *nd;
    unsigned int rc;
    CHAR szFullPath[MAX_PATH];

    errno = 0;

    if (!szPath) {
        errno = EFAULT;
        return (DIR *) 0;
    }
    if (szPath[0] == '\0') {
        errno = ENOTDIR;
        return (DIR *) 0;
    }
    /* Attempt to determine if the given path really is a directory. */
    rc = GetFileAttributes(szPath);
    if (rc == (unsigned int) -1) {
        /* call GetLastError for more error info */
        errno = ENOENT;
        return (DIR *) 0;
    }
    if (!(rc & FILE_ATTRIBUTE_DIRECTORY)) {
        /* Error, entry exists but not a directory. */
        errno = ENOTDIR;
        return (DIR *) 0;
    }
    /* Make an absolute pathname.  */
    _fullpath(szFullPath, szPath, MAX_PATH);

    /* Allocate enough space to store DIR structure and the complete
     * directory path given. */
    nd = (DIR *) malloc(sizeof(DIR) + (strlen(szFullPath)
                                       + strlen(SLASH)
                                       + strlen(SUFFIX) + 1)
                        * sizeof(CHAR));

    if (!nd) {
        /* Error, out of memory. */
        errno = ENOMEM;
        return (DIR *) 0;
    }
    /* Create the search expression. */
    strcpy(nd->dd_name, szFullPath);

    /* Add on a slash if the path does not end with one. */
    if (nd->dd_name[0] != '\0'
            && strchr(nd->dd_name, '/') != nd->dd_name
            + strlen(nd->dd_name) - 1
            && strchr(nd->dd_name, '\\') != nd->dd_name
            + strlen(nd->dd_name) - 1) {
        strcat(nd->dd_name, SLASH);
    }
    /* Add on the search pattern */
    strcat(nd->dd_name, SUFFIX);

    /* Initialize handle to -1 so that a premature closedir doesn't try
     * to call _findclose on it. */
    nd->dd_handle = -1;

    /* Initialize the status. */
    nd->dd_stat = 0;

    /* Initialize the dirent structure. ino and reclen are invalid under
     * Win32, and name simply points at the appropriate part of the
     * findfirst_t structure. */
    nd->dd_dir.d_ino = 0;
    nd->dd_dir.d_reclen = 0;
    nd->dd_dir.d_namlen = 0;
    memset(nd->dd_dir.d_name, 0, FILENAME_MAX);

    return nd;
}
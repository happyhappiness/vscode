int
closedir(DIR * dirp)
{
    int rc;

    errno = 0;
    rc = 0;

    if (!dirp) {
        errno = EFAULT;
        return -1;
    }
    if (dirp->dd_handle != -1) {
        rc = _findclose(dirp->dd_handle);
    }
    /* Delete the dir structure. */
    free(dirp);

    return rc;
}
void
seekdir(DIR * dirp, long lPos)
{
    errno = 0;

    if (!dirp) {
        errno = EFAULT;
        return;
    }
    if (lPos < -1) {
        /* Seeking to an invalid position. */
        errno = EINVAL;
        return;
    } else if (lPos == -1) {
        /* Seek past end. */
        if (dirp->dd_handle != -1) {
            _findclose(dirp->dd_handle);
        }
        dirp->dd_handle = -1;
        dirp->dd_stat = -1;
    } else {
        /* Rewind and read forward to the appropriate index. */
        rewinddir(dirp);

        while ((dirp->dd_stat < lPos) && readdir(dirp));
    }
}
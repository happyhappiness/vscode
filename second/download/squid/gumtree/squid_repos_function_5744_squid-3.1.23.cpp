void
rewinddir(DIR * dirp)
{
    errno = 0;

    if (!dirp) {
        errno = EFAULT;
        return;
    }
    if (dirp->dd_handle != -1) {
        _findclose(dirp->dd_handle);
    }
    dirp->dd_handle = -1;
    dirp->dd_stat = 0;
}
long
telldir(DIR * dirp)
{
    errno = 0;

    if (!dirp) {
        errno = EFAULT;
        return -1;
    }
    return dirp->dd_stat;
}
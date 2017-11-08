int execle(const char *path, const char *arg0, ...)
{
    errno = ENOSYS;
    return(-1);
}
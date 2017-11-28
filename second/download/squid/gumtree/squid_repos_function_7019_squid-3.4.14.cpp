int
WIN32_truncate(const char *pathname, off_t length)
{
    int fd;
    int res = -1;

    fd = open(pathname, O_RDWR);

    if (fd == -1)
        errno = EBADF;
    else {
        res = WIN32_ftruncate(fd, length);
        _close(fd);
    }

    return res;
}
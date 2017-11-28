int
file_open(const char *path, int mode)
{
    int fd;
    PROF_start(file_open);

    if (FILE_MODE(mode) == O_WRONLY)
        mode |= O_APPEND;

    errno = 0;

    fd = open(path, mode, 0644);

    ++ statCounter.syscalls.disk.opens;

    if (fd < 0) {
        int xerrno = errno;
        debugs(50, 3, "error opening file " << path << ": " << xstrerr(xerrno));
        fd = DISK_ERROR;
    } else {
        debugs(6, 5, "FD " << fd);
        commSetCloseOnExec(fd);
        fd_open(fd, FD_FILE, path);
    }

    PROF_stop(file_open);
    return fd;
}
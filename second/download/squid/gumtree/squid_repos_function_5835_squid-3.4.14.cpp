int aio_open(const char *path, int mode)
{
    HANDLE hndl;
    DWORD dwCreationDisposition;
    DWORD dwDesiredAccess;
    int fd;

    if (mode & O_WRONLY)
        mode |= O_APPEND;

    mode |= O_BINARY;

    errno = 0;

    if (mode & O_WRONLY)
        dwDesiredAccess = GENERIC_WRITE;
    else
        dwDesiredAccess = (mode & O_RDONLY) ? GENERIC_READ : GENERIC_READ | GENERIC_WRITE;

    if (mode & O_TRUNC)
        dwCreationDisposition = CREATE_ALWAYS;
    else
        dwCreationDisposition = (mode & O_CREAT) ? OPEN_ALWAYS : OPEN_EXISTING;

    if ((hndl = CreateFile(path,	                /* file name               */
                           dwDesiredAccess,	        /* access mode             */
                           0,			            /* share mode              */
                           NULL,			        /* SD                      */
                           dwCreationDisposition,	/* how to create           */
                           FILE_FLAG_OVERLAPPED,	/* file attributes         */
                           NULL			            /* handle to template file */
                          )) != INVALID_HANDLE_VALUE) {
        ++ statCounter.syscalls.disk.opens;
        fd = _open_osfhandle((long) hndl, 0);
        commSetCloseOnExec(fd);
        fd_open(fd, FD_FILE, path);
    } else {
        errno = GetLastError();
        fd = DISK_ERROR;
    }

    return fd;
}
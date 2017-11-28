void aio_close(int fd)
{
    CloseHandle((HANDLE)_get_osfhandle(fd));
    fd_close(fd);
    ++ statCounter.syscalls.disk.closes;
}
int
WIN32_ftruncate(int fd, off_t size)
{
    HANDLE hfile;
    unsigned int curpos;

    if (fd < 0)
        return -1;

    hfile = (HANDLE) _get_osfhandle(fd);
    curpos = SetFilePointer(hfile, 0, NULL, FILE_CURRENT);
    if (curpos == 0xFFFFFFFF
            || SetFilePointer(hfile, size, NULL, FILE_BEGIN) == 0xFFFFFFFF
            || !SetEndOfFile(hfile)) {
        int error = GetLastError();

        switch (error) {
        case ERROR_INVALID_HANDLE:
            errno = EBADF;
            break;
        default:
            errno = EIO;
            break;
        }

        return -1;
    }
    return 0;
}
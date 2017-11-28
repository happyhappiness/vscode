int
_free_osfhnd(int filehandle)
{
    if (((unsigned) filehandle < SQUID_MAXFD) &&
            (_osfile(filehandle) & FOPEN) &&
            (_osfhnd(filehandle) != (long) INVALID_HANDLE_VALUE)) {
        switch (filehandle) {
        case 0:
            SetStdHandle(STD_INPUT_HANDLE, NULL);
            break;
        case 1:
            SetStdHandle(STD_OUTPUT_HANDLE, NULL);
            break;
        case 2:
            SetStdHandle(STD_ERROR_HANDLE, NULL);
            break;
        }
        _osfhnd(filehandle) = (long) INVALID_HANDLE_VALUE;
        return (0);
    } else {
        errno = EBADF;      /* bad handle */
        _doserrno = 0L;     /* not an OS error */
        return -1;
    }
}
void
WIN32_maperror(unsigned long WIN32_oserrno)
{
    _doserrno = WIN32_oserrno;
    for (size_t i = 0; i < (sizeof(errortable) / sizeof(struct errorentry)); ++i) {
        if (WIN32_oserrno == errortable[i].WIN32_code) {
            errno = errortable[i].POSIX_errno;
            return;
        }
    }
    if (WIN32_oserrno >= MIN_EACCES_RANGE && WIN32_oserrno <= MAX_EACCES_RANGE)
        errno = EACCES;
    else if (WIN32_oserrno >= MIN_EXEC_ERROR && WIN32_oserrno <= MAX_EXEC_ERROR)
        errno = ENOEXEC;
    else
        errno = EINVAL;
}
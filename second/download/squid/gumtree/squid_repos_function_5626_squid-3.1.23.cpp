const char *
WIN32_strerror(int err)
{
    static char xbstrerror_buf[BUFSIZ];

    if (err < 0 || err >= sys_nerr)
        strncpy(xbstrerror_buf, wsastrerror(err), BUFSIZ);
    else
        strncpy(xbstrerror_buf, strerror(err), BUFSIZ);
    return xbstrerror_buf;
}
const char *
xstrerr(int error)
{
    static char xstrerror_buf[BUFSIZ];

    if (error == 0)
        return "(0) No error.";

#if _SQUID_WINDOWS_
    // Description of WSAGetLastError()
    for (size_t i = 0; i < sizeof(_wsaerrtext) / sizeof(struct _wsaerrtext); ++i) {
        if (_wsaerrtext[i].err == error) {
            // small optimization, save using a temporary buffer and two copies...
            snprintf(xstrerror_buf, BUFSIZ, "(%d) %s, %s", error, _wsaerrtext[i].errconst, _wsaerrtext[i].errdesc);
            return xstrerror_buf;
        }
    }
#endif

    const char *errmsg = strerror(error);

    if (!errmsg || !*errmsg)
        errmsg = "Unknown error";

    snprintf(xstrerror_buf, BUFSIZ, "(%d) %s", error, errmsg);

    return xstrerror_buf;
}
const char *
xstrerr(int error)
{
    static char xstrerror_buf[BUFSIZ];
    const char *errmsg;

    errmsg = strerror(error);

    if (!errmsg || !*errmsg)
        errmsg = "Unknown error";

    snprintf(xstrerror_buf, BUFSIZ, "(%d) %s", error, errmsg);

    return xstrerror_buf;
}
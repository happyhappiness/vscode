const char *
wsastrerror(int err)
{
    static char xwsaerror_buf[BUFSIZ];
    int i, errind = -1;

    if (err == 0)
        return "(0) No error.";
    for (i = 0; i < sizeof(_wsaerrtext) / sizeof(struct _wsaerrtext); i++) {
        if (_wsaerrtext[i].err != err)
            continue;
        errind = i;
        break;
    }
    if (errind == -1)
        snprintf(xwsaerror_buf, BUFSIZ, "Unknown");
    else
        snprintf(xwsaerror_buf, BUFSIZ, "%s, %s", _wsaerrtext[errind].errconst, _wsaerrtext[errind].errdesc);
    return xwsaerror_buf;
}
static char *
escapeIAC(const char *buf)
{
    int n;
    char *ret;
    unsigned const char *p;
    unsigned char *r;

    for (p = (unsigned const char *)buf, n = 1; *p; n++, p++)
        if (*p == 255)
            n++;

    ret = (char *)xmalloc(n);

    for (p = (unsigned const char *)buf, r=(unsigned char *)ret; *p; p++) {
        *r++ = *p;

        if (*p == 255)
            *r++ = 255;
    }

    *r++ = '\0';
    assert((r - (unsigned char *)ret) == n );
    return ret;
}
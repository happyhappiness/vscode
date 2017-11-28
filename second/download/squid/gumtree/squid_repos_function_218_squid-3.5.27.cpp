char *
mkrfc1123(t)
time_t *t;
{
    static char buf[128];
    struct tm *gmt = gmtime(t);
    buf[0] = '\0';
    (void) strftime(buf, 127, RFC1123_STRFTIME, gmt);
    return buf;
}
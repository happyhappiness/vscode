static int
parse_status_line(const char *sline, const char **statusStr)
{
    const char *sp = strchr(sline, ' ');

    if (statusStr)
        *statusStr = NULL;

    if (strncasecmp(sline, "HTTP/", 5) || !sp)
        return -1;

    while (xisspace(*++sp));
    if (!xisdigit(*sp))
        return -1;

    if (statusStr)
        *statusStr = sp;

    return atoi(sp);
}
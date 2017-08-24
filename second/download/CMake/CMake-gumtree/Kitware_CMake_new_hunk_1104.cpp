    int fd;
    const char *mode;
{
    char name[46];      /* allow for up to 128-bit integers */

    if (fd < 0) return (gzFile)Z_NULL;
    sprintf(name, "<fd:%d>", fd); /* for debugging */

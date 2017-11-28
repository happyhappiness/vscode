static const char *
dots_fill(size_t len)
{
    static char buf[256];
    size_t i = 0;

    if (len > Config.Ftp.list_width) {
        memset(buf, ' ', 256);
        buf[0] = '\n';
        buf[Config.Ftp.list_width + 4] = '\0';
        return buf;
    }

    for (i = len; i < Config.Ftp.list_width; i++)
        buf[i - len] = (i % 2) ? '.' : ' ';

    buf[i - len] = '\0';

    return buf;
}
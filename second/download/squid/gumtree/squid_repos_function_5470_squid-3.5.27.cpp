static int
is_month(const char *buf)
{
    int i;

    for (i = 0; i < 12; ++i)
        if (!strcasecmp(buf, Month[i]))
            return 1;

    return 0;
}
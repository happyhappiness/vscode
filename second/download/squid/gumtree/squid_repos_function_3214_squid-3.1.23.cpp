void
URLHostName::trimAuth()
{
    char *t;

    if ((t = strrchr(Host, '@'))) {
        t++;
        xmemmove(Host, t, strlen(t) + 1);
    }
}
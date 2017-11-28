void
URLHostName::trimAuth()
{
    char *t;

    if ((t = strrchr(Host, '@'))) {
        ++t;
        memmove(Host, t, strlen(t) + 1);
    }
}
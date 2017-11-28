void
URLHostName::trimTrailingChars()
{
    char *t;

    if ((t = strchr(Host, '/')))
        *t = '\0';

    if ((t = strrchr(Host, ':')))
        *t = '\0';

    if ((t = strchr(Host, ']')))
        *t = '\0';
}
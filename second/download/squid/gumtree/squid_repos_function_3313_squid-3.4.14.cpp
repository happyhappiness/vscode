char *
URLHostName::extract(char const *aUrl)
{
    init(aUrl);
    findHostStart();

    if (hostStart == NULL)
        return NULL;

    xstrncpy(Host, hostStart, SQUIDHOSTNAMELEN);

    trimTrailingChars();

    trimAuth();

    return Host;
}
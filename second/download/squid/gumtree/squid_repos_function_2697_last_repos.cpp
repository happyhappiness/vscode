const char *
internalHostname(void)
{
    LOCAL_ARRAY(char, host, SQUIDHOSTNAMELEN + 1);
    xstrncpy(host, getMyHostname(), SQUIDHOSTNAMELEN);

    /* For IPv6 addresses also check for a colon */
    if (Config.appendDomain && !strchr(host, '.') && !strchr(host, ':'))
        strncat(host, Config.appendDomain, SQUIDHOSTNAMELEN -
                strlen(host) - 1);

    Tolower(host);

    return host;
}
const char *
getfullhostname(void)
{
    const struct hostent *hp = NULL;
    static char buf[RFC2181_MAXHOSTNAMELEN + 1];

    if (gethostname(buf, RFC2181_MAXHOSTNAMELEN) < 0)
        return NULL;
    /** \todo convert this to a getaddrinfo() call */
    if ((hp = gethostbyname(buf)) != NULL)
        xstrncpy(buf, hp->h_name, RFC2181_MAXHOSTNAMELEN);
    return buf;
}
static bool
sameUrlHosts(const char *url1, const char *url2)
{
    // XXX: Want urlHostname() here, but it uses static storage and copying
    const char *host1 = strchr(url1, ':');
    const char *host2 = strchr(url2, ':');

    if (host1 && host2) {
        // skip scheme slashes
        do {
            ++host1;
            ++host2;
        } while (*host1 == '/' && *host2 == '/');

        if (!*host1)
            return false; // no host

        // increment while the same until we reach the end of the URL/host
        while (*host1 && *host1 != '/' && *host1 == *host2) {
            ++host1;
            ++host2;
        }
        return *host1 == *host2;
    }

    return false; // no URL scheme
}
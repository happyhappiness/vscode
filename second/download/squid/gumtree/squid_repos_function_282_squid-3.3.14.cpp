int
get_hostname_list(struct main_args *margs, struct hstruct **hlist, int nhosts, char *name)
{
    /*
     * char host[sysconf(_SC_HOST_NAME_MAX)];
     */
    char host[1024];
    struct addrinfo *hres = NULL, *hres_list;
    int rc, count;
    struct hstruct *hp = NULL;

    if (!name)
        return (nhosts);

    hp = *hlist;
    rc = getaddrinfo((const char *) name, NULL, NULL, &hres);
    if (rc != 0) {
        error((char *) "%s| %s: ERROR: Error while resolving hostname with getaddrinfo: %s\n", LogTime(), PROGRAM, gai_strerror(rc));
        return (nhosts);
    }
    hres_list = hres;
    count = 0;
    while (hres_list) {
        ++count;
        hres_list = hres_list->ai_next;
    }
    hres_list = hres;
    count = 0;
    while (hres_list) {
        rc = getnameinfo(hres_list->ai_addr, hres_list->ai_addrlen, host, sizeof(host), NULL, 0, 0);
        if (rc != 0) {
            error((char *) "%s| %s: ERROR: Error while resolving ip address with getnameinfo: %s\n", LogTime(), PROGRAM, gai_strerror(rc));
            freeaddrinfo(hres);
            *hlist = hp;
            return (nhosts);
        }
        ++count;
        debug((char *) "%s| %s: DEBUG: Resolved address %d of %s to %s\n", LogTime(), PROGRAM, count, name, host);

        hp = (struct hstruct *) xrealloc(hp, sizeof(struct hstruct) * (nhosts + 1));
        hp[nhosts].host = xstrdup(host);
        hp[nhosts].port = -1;
        hp[nhosts].priority = -1;
        hp[nhosts].weight = -1;
        ++nhosts;

        hres_list = hres_list->ai_next;
    }

    freeaddrinfo(hres);
    *hlist = hp;
    return (nhosts);
}
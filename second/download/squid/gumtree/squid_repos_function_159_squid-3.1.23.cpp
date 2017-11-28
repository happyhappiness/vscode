char *gethost_name(void)
{
    char      hostname[sysconf(_SC_HOST_NAME_MAX)];
    struct addrinfo *hres=NULL, *hres_list;
    int rc,count;

    rc = gethostname(hostname,sysconf(_SC_HOST_NAME_MAX));
    if (rc) {
        fprintf(stderr, "%s| %s: ERROR: resolving hostname '%s' failed\n", LogTime(), PROGRAM, hostname);
        return NULL;
    }
    rc = xgetaddrinfo(hostname,NULL,NULL,&hres);
    if (rc != 0) {
        fprintf(stderr, "%s| %s: ERROR: resolving hostname with getaddrinfo: %s failed\n", LogTime(), PROGRAM, xgai_strerror(rc));
        return NULL;
    }
    hres_list=hres;
    count=0;
    while (hres_list) {
        count++;
        hres_list=hres_list->ai_next;
    }
    rc = xgetnameinfo (hres->ai_addr, hres->ai_addrlen,hostname, sizeof (hostname), NULL, 0, 0);
    if (rc != 0) {
        fprintf(stderr, "%s| %s: ERROR: resolving ip address with getnameinfo: %s failed\n", LogTime(), PROGRAM, xgai_strerror(rc));
        xfreeaddrinfo(hres);
        return NULL ;
    }

    xfreeaddrinfo(hres);
    hostname[sysconf(_SC_HOST_NAME_MAX)-1]='\0';
    return(xstrdup(hostname));
}
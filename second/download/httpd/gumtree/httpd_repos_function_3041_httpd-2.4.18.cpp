static unsigned long parse_addr(const char *w, unsigned short *ports)
{
    struct hostent *hep;
    unsigned long my_addr;
    char *p;

    p = strchr(w, ':');
    if (ports != NULL) {
        *ports = 0;
        if (p != NULL && strcmp(p + 1, "*") != 0)
            *ports = atoi(p + 1);
    }

    if (p != NULL)
        *p = '\0';
    if (strcmp(w, "*") == 0) {
        if (p != NULL)
            *p = ':';
        return htonl(INADDR_ANY);
    }

    my_addr = apr_inet_addr((char *)w);
    if (my_addr != INADDR_NONE) {
        if (p != NULL)
            *p = ':';
        return my_addr;
    }

    hep = gethostbyname(w);

    if ((!hep) || (hep->h_addrtype != AF_INET || !hep->h_addr_list[0])) {
        /* XXX Should be echoing by h_errno the actual failure, no?
         * ap_log_error would be good here.  Better yet - APRize.
         */
        fprintf(stderr, "Cannot resolve host name %s --- exiting!\n", w);
        exit(1);
    }

    if (hep->h_addr_list[1]) {
        fprintf(stderr, "Host %s has multiple addresses ---\n", w);
        fprintf(stderr, "you must choose one explicitly for use as\n");
        fprintf(stderr, "a secure port.  Exiting!!!\n");
        exit(1);
    }

    if (p != NULL)
        *p = ':';

    return ((struct in_addr *) (hep->h_addr))->s_addr;
}
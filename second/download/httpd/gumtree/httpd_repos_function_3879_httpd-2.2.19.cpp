static apr_status_t find_addresses(apr_sockaddr_t **sa, 
                                   const char *hostname, apr_int32_t family,
                                   apr_port_t port, apr_int32_t flags, 
                                   apr_pool_t *p)
{
    struct hostent *hp;
    apr_sockaddr_t *prev_sa;
    int curaddr;
#if APR_HAS_THREADS && !defined(GETHOSTBYNAME_IS_THREAD_SAFE) && \
    defined(HAVE_GETHOSTBYNAME_R) && !defined(BEOS)
#ifdef GETHOSTBYNAME_R_HOSTENT_DATA
    struct hostent_data hd;
#else
    /* If you see ERANGE, that means GETHOSBYNAME_BUFLEN needs to be
     * bumped. */
    char tmp[GETHOSTBYNAME_BUFLEN];
#endif
    int hosterror;
#endif
    struct hostent hs;
    struct in_addr ipaddr;
    char *addr_list[2];
    const char *orig_hostname = hostname;

    if (hostname == NULL) {
        /* if we are given a NULL hostname, assume '0.0.0.0' */
        hostname = "0.0.0.0";
    }

    if (*hostname >= '0' && *hostname <= '9' &&
        strspn(hostname, "0123456789.") == strlen(hostname)) {

        ipaddr.s_addr = inet_addr(hostname);
        addr_list[0] = (char *)&ipaddr;
        addr_list[1] = NULL; /* just one IP in list */
        hs.h_addr_list = (char **)addr_list;
        hp = &hs;
    }
    else {
#if APR_HAS_THREADS && !defined(GETHOSTBYNAME_IS_THREAD_SAFE) && \
    defined(HAVE_GETHOSTBYNAME_R) && !defined(BEOS)
#if defined(GETHOSTBYNAME_R_HOSTENT_DATA)
        /* AIX, HP/UX, D/UX et alia */
        gethostbyname_r(hostname, &hs, &hd);
        hp = &hs;
#else
#if defined(GETHOSTBYNAME_R_GLIBC2)
        /* Linux glibc2+ */
        gethostbyname_r(hostname, &hs, tmp, GETHOSTBYNAME_BUFLEN - 1, 
                        &hp, &hosterror);
#else
        /* Solaris, Irix et alia */
        hp = gethostbyname_r(hostname, &hs, tmp, GETHOSTBYNAME_BUFLEN - 1,
                             &hosterror);
#endif /* !defined(GETHOSTBYNAME_R_GLIBC2) */
        if (!hp) {
            return (hosterror + APR_OS_START_SYSERR);
        }
#endif /* !defined(GETHOSTBYNAME_R_HOSTENT_DATA) */
#else
        hp = gethostbyname(hostname);
#endif

        if (!hp) {
#ifdef WIN32
            return apr_get_netos_error();
#else
            return (h_errno + APR_OS_START_SYSERR);
#endif
        }
    }

    prev_sa = NULL;
    curaddr = 0;
    while (hp->h_addr_list[curaddr]) {
        apr_sockaddr_t *new_sa = apr_pcalloc(p, sizeof(apr_sockaddr_t));

        new_sa->pool = p;
        new_sa->sa.sin.sin_addr = *(struct in_addr *)hp->h_addr_list[curaddr];
        apr_sockaddr_vars_set(new_sa, AF_INET, port);

        if (!prev_sa) { /* first element in new list */
            if (orig_hostname) {
                new_sa->hostname = apr_pstrdup(p, orig_hostname);
            }
            *sa = new_sa;
        }
        else {
            new_sa->hostname = prev_sa->hostname;
            prev_sa->next = new_sa;
        }

        prev_sa = new_sa;
        ++curaddr;
    }

    return APR_SUCCESS;
}
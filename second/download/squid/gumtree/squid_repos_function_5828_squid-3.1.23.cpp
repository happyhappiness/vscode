int
xgetaddrinfo (const char *nodename, const char *servname,
              const struct addrinfo *hints, struct addrinfo **res)
{
    struct hostent *hp;
    struct servent *servent;
    const char *socktype;
    int port;
    struct addrinfo hint, result;
    struct addrinfo *ai, *sai, *eai;
    char **addrs;

    if (servname == NULL && nodename == NULL)
        return EAI_NONAME;

    memset (&result, 0, sizeof result);

    /* default for hints */
    if (hints == NULL) {
        memset (&hint, 0, sizeof hint);
        hint.ai_family = PF_UNSPEC;
        hints = &hint;
    }

    if (servname == NULL)
        port = 0;
    else {
        /* check for tcp or udp sockets only */
        if (hints->ai_socktype == SOCK_STREAM)
            socktype = "tcp";
        else if (hints->ai_socktype == SOCK_DGRAM)
            socktype = "udp";
        else
            return EAI_SERVICE;
        result.ai_socktype = hints->ai_socktype;

        /* Note: maintain port in host byte order to make debugging easier */
        if (isdigit (*servname))
            port = strtol (servname, NULL, 10);
        else if ((servent = getservbyname (servname, socktype)) != NULL)
            port = ntohs (servent->s_port);
        else
            return EAI_NONAME;
    }

    /* if nodename == NULL refer to the local host for a client or any
       for a server */
    if (nodename == NULL) {
        struct sockaddr_in sin;

        /* check protocol family is PF_UNSPEC or PF_INET - could try harder
           for IPv6 but that's more code than I'm prepared to write */
        if (hints->ai_family == PF_UNSPEC || hints->ai_family == PF_INET)
            result.ai_family = AF_INET;
        else
            return EAI_FAMILY;

        sin.sin_family = result.ai_family;
        sin.sin_port = htons (port);
        if (hints->ai_flags & AI_PASSIVE)
            sin.sin_addr.s_addr = htonl (INADDR_ANY);
        else
            sin.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
        /* Duplicate result and addr and return */
        *res = dup_addrinfo (&result, &sin, sizeof sin);
        return (*res == NULL) ? EAI_MEMORY : 0;
    }

    /* If AI_NUMERIC is specified, use xinet_pton to translate numbers and
       dots notation. */
    if (hints->ai_flags & AI_NUMERICHOST) {
        struct sockaddr_in sin;

        /* check protocol family is PF_UNSPEC or PF_INET */
        if (hints->ai_family == PF_UNSPEC || hints->ai_family == PF_INET)
            result.ai_family = AF_INET;
        else
            return EAI_FAMILY;

        sin.sin_family = result.ai_family;
        sin.sin_port = htons (port);
        if (xinet_pton(result.ai_family, nodename, &sin.sin_addr))
            return EAI_NONAME;
        sin.sin_addr.s_addr = inet_addr (nodename);
        /* Duplicate result and addr and return */
        *res = dup_addrinfo (&result, &sin, sizeof sin);
        return (*res == NULL) ? EAI_MEMORY : 0;
    }

#if HAVE_H_ERRNO
    h_errno = 0;
#endif
    errno = 0;
    hp = gethostbyname(nodename);
    if (hp == NULL) {
#ifdef EAI_SYSTEM
        if (errno != 0) {
            return EAI_SYSTEM;
        }
#endif
        switch (h_errno) {
        case HOST_NOT_FOUND:
            return EAI_NODATA;
        case NO_DATA:
            return EAI_NODATA;
#if defined(NO_ADDRESS) && NO_ADDRESS != NO_DATA
        case NO_ADDRESS:
            return EAI_NODATA;
#endif
        case NO_RECOVERY:
            return EAI_FAIL;
        case TRY_AGAIN:
            return EAI_AGAIN;
        default:
            return EAI_FAIL;
        }
        return EAI_FAIL;
    }

    /* Check that the address family is acceptable.
     */
    switch (hp->h_addrtype) {
    case AF_INET:
        if (!(hints->ai_family == PF_UNSPEC || hints->ai_family == PF_INET))
            return EAI_FAMILY;
        break;
    case AF_INET6:
        if (!(hints->ai_family == PF_UNSPEC || hints->ai_family == PF_INET6))
            return EAI_FAMILY;
        break;
    default:
        return EAI_FAMILY;
    }

    /* For each element pointed to by hp, create an element in the
       result linked list. */
    sai = eai = NULL;
    for (addrs = hp->h_addr_list; *addrs != NULL; addrs++) {
        struct sockaddr sa;
        size_t addrlen;

        if (hp->h_length < 1)
            continue;
        sa.sa_family = hp->h_addrtype;
        switch (hp->h_addrtype) {
        case AF_INET:
            ((struct sockaddr_in *) &sa)->sin_port = htons (port);
            memcpy (&((struct sockaddr_in *) &sa)->sin_addr,
                    *addrs, hp->h_length);
            addrlen = sizeof (struct sockaddr_in);
            break;
        case AF_INET6:
#if SIN6_LEN
            ((struct sockaddr_in6 *) &sa)->sin6_len = hp->h_length;
#endif
            ((struct sockaddr_in6 *) &sa)->sin6_port = htons (port);
            memcpy (&((struct sockaddr_in6 *) &sa)->sin6_addr,
                    *addrs, hp->h_length);
            addrlen = sizeof (struct sockaddr_in6);
            break;
        default:
            continue;
        }

        result.ai_family = hp->h_addrtype;
        ai = dup_addrinfo (&result, &sa, addrlen);
        if (ai == NULL) {
            xfreeaddrinfo (sai);
            return EAI_MEMORY;
        }
        if (sai == NULL)
            sai = ai;
        else
            eai->ai_next = ai;
        eai = ai;
    }

    if (sai == NULL) {
        return EAI_NODATA;
    }

    if (hints->ai_flags & AI_CANONNAME) {
        sai->ai_canonname = malloc (strlen (hp->h_name) + 1);
        if (sai->ai_canonname == NULL) {
            xfreeaddrinfo (sai);
            return EAI_MEMORY;
        }
        strcpy (sai->ai_canonname, hp->h_name);
    }

    *res = sai;
    return 0;
}
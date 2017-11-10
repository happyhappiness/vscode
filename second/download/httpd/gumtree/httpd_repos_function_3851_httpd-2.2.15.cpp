static apr_status_t call_resolver(apr_sockaddr_t **sa,
                                  const char *hostname, apr_int32_t family,
                                  apr_port_t port, apr_int32_t flags, 
                                  apr_pool_t *p)
{
    struct addrinfo hints, *ai, *ai_list;
    apr_sockaddr_t *prev_sa;
    int error;
    char *servname = NULL; 

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = SOCK_STREAM;
#ifdef HAVE_GAI_ADDRCONFIG
    if (family == APR_UNSPEC) {
        /* By default, only look up addresses using address types for
         * which a local interface is configured, i.e. no IPv6 if no
         * IPv6 interfaces configured. */
        hints.ai_flags = AI_ADDRCONFIG;
    }
#endif
    if(hostname == NULL) {
#ifdef AI_PASSIVE 
        /* If hostname is NULL, assume we are trying to bind to all
         * interfaces. */
        hints.ai_flags |= AI_PASSIVE;
#endif
        /* getaddrinfo according to RFC 2553 must have either hostname
         * or servname non-NULL.
         */
#ifdef OSF1
        /* The Tru64 5.0 getaddrinfo() can only resolve services given
         * by the name listed in /etc/services; a numeric or unknown
         * servname gets an EAI_SERVICE error.  So just resolve the
         * appropriate anyaddr and fill in the port later. */
        hostname = family == AF_INET6 ? "::" : "0.0.0.0";
        servname = NULL;
#ifdef AI_NUMERICHOST
        hints.ai_flags |= AI_NUMERICHOST;
#endif
#else
#ifdef _AIX
        /* But current AIX getaddrinfo() doesn't like servname = "0";
         * the "1" won't hurt since we use the port parameter to fill
         * in the returned socket addresses later
         */
        if (!port) {
            servname = "1";
        }
        else
#endif /* _AIX */
        servname = apr_itoa(p, port);
#endif /* OSF1 */
    }
    error = getaddrinfo(hostname, servname, &hints, &ai_list);
#ifdef HAVE_GAI_ADDRCONFIG
    if (error == EAI_BADFLAGS && family == APR_UNSPEC) {
        /* Retry with no flags if AI_ADDRCONFIG was rejected. */
        hints.ai_flags = 0;
        error = getaddrinfo(hostname, servname, &hints, &ai_list);
    }
#endif
    if (error) {
#ifndef WIN32
        if (error == EAI_SYSTEM) {
            return errno;
        }
        else 
#endif
        {
            /* issues with representing this with APR's error scheme:
             * glibc uses negative values for these numbers, perhaps so 
             * they don't conflict with h_errno values...  Tru64 uses 
             * positive values which conflict with h_errno values
             */
#if defined(NEGATIVE_EAI)
            error = -error;
#endif
            return error + APR_OS_START_EAIERR;
        }
    }

    prev_sa = NULL;
    ai = ai_list;
    while (ai) { /* while more addresses to report */
        apr_sockaddr_t *new_sa;

        /* Ignore anything bogus: getaddrinfo in some old versions of
         * glibc will return AF_UNIX entries for APR_UNSPEC+AI_PASSIVE
         * lookups. */
#if APR_HAVE_IPV6
        if (ai->ai_family != AF_INET && ai->ai_family != AF_INET6) {
#else
        if (ai->ai_family != AF_INET) {
#endif
            ai = ai->ai_next;
            continue;
        }

        new_sa = apr_pcalloc(p, sizeof(apr_sockaddr_t));

        new_sa->pool = p;
        memcpy(&new_sa->sa, ai->ai_addr, ai->ai_addrlen);
        apr_sockaddr_vars_set(new_sa, ai->ai_family, port);

        if (!prev_sa) { /* first element in new list */
            if (hostname) {
                new_sa->hostname = apr_pstrdup(p, hostname);
            }
            *sa = new_sa;
        }
        else {
            new_sa->hostname = prev_sa->hostname;
            prev_sa->next = new_sa;
        }

        prev_sa = new_sa;
        ai = ai->ai_next;
    }
    freeaddrinfo(ai_list);
    return APR_SUCCESS;
}

static apr_status_t find_addresses(apr_sockaddr_t **sa, 
                                   const char *hostname, apr_int32_t family,
                                   apr_port_t port, apr_int32_t flags, 
                                   apr_pool_t *p)
{
    if (flags & APR_IPV4_ADDR_OK) {
        apr_status_t error = call_resolver(sa, hostname, AF_INET, port, flags, p);

#if APR_HAVE_IPV6
        if (error) {
            family = AF_INET6; /* try again */
        }
        else
#endif
        return error;
    }
#if APR_HAVE_IPV6
    else if (flags & APR_IPV6_ADDR_OK) {
        apr_status_t error = call_resolver(sa, hostname, AF_INET6, port, flags, p);

        if (error) {
            family = AF_INET; /* try again */
        }
        else {
            return APR_SUCCESS;
        }
    }
#endif

    return call_resolver(sa, hostname, family, port, flags, p);
}

#else /* end of HAVE_GETADDRINFO code */

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

#endif /* end of !HAVE_GETADDRINFO code */

APR_DECLARE(apr_status_t) apr_sockaddr_info_get(apr_sockaddr_t **sa,
                                                const char *hostname, 
                                                apr_int32_t family, apr_port_t port,
                                                apr_int32_t flags, apr_pool_t *p)
{
    apr_int32_t masked;
    *sa = NULL;

    if ((masked = flags & (APR_IPV4_ADDR_OK | APR_IPV6_ADDR_OK))) {
        if (!hostname ||
            family != APR_UNSPEC ||
            masked == (APR_IPV4_ADDR_OK | APR_IPV6_ADDR_OK)) {
            return APR_EINVAL;
        }
#if !APR_HAVE_IPV6
        if (flags & APR_IPV6_ADDR_OK) {
            return APR_ENOTIMPL;
        }
#endif
    }
#if !APR_HAVE_IPV6
    /* What may happen is that APR is not IPv6-enabled, but we're still
     * going to call getaddrinfo(), so we have to tell the OS we only
     * want IPv4 addresses back since we won't know what to do with
     * IPv6 addresses.
     */
    if (family == APR_UNSPEC) {
        family = APR_INET;
    }
#endif

    return find_addresses(sa, hostname, family, port, flags, p);
}

APR_DECLARE(apr_status_t) apr_getnameinfo(char **hostname,
                                          apr_sockaddr_t *sockaddr,
                                          apr_int32_t flags)
{
#if defined(HAVE_GETNAMEINFO)
    int rc;
#if defined(NI_MAXHOST)
    char tmphostname[NI_MAXHOST];
#else
    char tmphostname[256];
#endif

    /* don't know if it is portable for getnameinfo() to set h_errno;
     * clear it then see if it was set */
    SET_H_ERRNO(0);

    /* default flags are NI_NAMREQD; otherwise, getnameinfo() will return
     * a numeric address string if it fails to resolve the host name;
     * that is *not* what we want here
     *
     * For IPv4-mapped IPv6 addresses, drop down to IPv4 before calling
     * getnameinfo() to avoid getnameinfo bugs (MacOS X, glibc).
     */
#if APR_HAVE_IPV6
    if (sockaddr->family == AF_INET6 &&
        IN6_IS_ADDR_V4MAPPED(&sockaddr->sa.sin6.sin6_addr)) {
        struct sockaddr_in tmpsa;
        tmpsa.sin_family = AF_INET;
        tmpsa.sin_port = 0;
        tmpsa.sin_addr.s_addr = ((apr_uint32_t *)sockaddr->ipaddr_ptr)[3];
#ifdef SIN6_LEN
        tmpsa.sin_len = sizeof(tmpsa);
#endif

        rc = getnameinfo((const struct sockaddr *)&tmpsa, sizeof(tmpsa),
                         tmphostname, sizeof(tmphostname), NULL, 0,
                         flags != 0 ? flags : NI_NAMEREQD);
    }
    else
#endif
    rc = getnameinfo((const struct sockaddr *)&sockaddr->sa, sockaddr->salen,
                     tmphostname, sizeof(tmphostname), NULL, 0,
                     flags != 0 ? flags : NI_NAMEREQD);
    if (rc != 0) {
        *hostname = NULL;

#ifndef WIN32
        /* something went wrong. Look at the EAI_ error code */
        if (rc == EAI_SYSTEM) {
            /* EAI_SYSTEM      System error returned in errno. */
            /* IMHO, Implementations that set h_errno a simply broken. */
            if (h_errno) { /* for broken implementations which set h_errno */
                return h_errno + APR_OS_START_SYSERR;
            }
            else { /* "normal" case */
                return errno + APR_OS_START_SYSERR;
            }
        }
        else 
#endif
        {
#if defined(NEGATIVE_EAI)
            if (rc < 0) rc = -rc;
#endif
            return rc + APR_OS_START_EAIERR; /* return the EAI_ error */
        }
    }
    *hostname = sockaddr->hostname = apr_pstrdup(sockaddr->pool, 
                                                 tmphostname);
    return APR_SUCCESS;
#else
#if APR_HAS_THREADS && !defined(GETHOSTBYADDR_IS_THREAD_SAFE) && \
    defined(HAVE_GETHOSTBYADDR_R) && !defined(BEOS)
#ifdef GETHOSTBYNAME_R_HOSTENT_DATA
    struct hostent_data hd;
#else
    char tmp[GETHOSTBYNAME_BUFLEN];
#endif
    int hosterror;
    struct hostent hs, *hptr;

#if defined(GETHOSTBYNAME_R_HOSTENT_DATA)
    /* AIX, HP/UX, D/UX et alia */
    gethostbyaddr_r((char *)&sockaddr->sa.sin.sin_addr, 
                  sizeof(struct in_addr), AF_INET, &hs, &hd);
    hptr = &hs;
#else
#if defined(GETHOSTBYNAME_R_GLIBC2)
    /* Linux glibc2+ */
    gethostbyaddr_r((char *)&sockaddr->sa.sin.sin_addr, 
                    sizeof(struct in_addr), AF_INET,
                    &hs, tmp, GETHOSTBYNAME_BUFLEN - 1, &hptr, &hosterror);
#else
    /* Solaris, Irix et alia */
    hptr = gethostbyaddr_r((char *)&sockaddr->sa.sin.sin_addr, 
                           sizeof(struct in_addr), AF_INET,
                           &hs, tmp, GETHOSTBYNAME_BUFLEN, &hosterror);
#endif /* !defined(GETHOSTBYNAME_R_GLIBC2) */
    if (!hptr) {
        *hostname = NULL;
        return hosterror + APR_OS_START_SYSERR;
    }
#endif /* !defined(GETHOSTBYNAME_R_HOSTENT_DATA) */
#else
    struct hostent *hptr;
    hptr = gethostbyaddr((char *)&sockaddr->sa.sin.sin_addr, 
                         sizeof(struct in_addr), AF_INET);
#endif

    if (hptr) {
        *hostname = sockaddr->hostname = apr_pstrdup(sockaddr->pool, hptr->h_name);
        return APR_SUCCESS;
    }
    *hostname = NULL;
#if defined(WIN32)
    return apr_get_netos_error();
#elif defined(OS2)
    return h_errno;
#else
    return h_errno + APR_OS_START_SYSERR;
#endif
#endif
}

APR_DECLARE(apr_status_t) apr_getservbyname(apr_sockaddr_t *sockaddr,
                                            const char *servname)
{
#if APR_HAS_THREADS && !defined(GETSERVBYNAME_IS_THREAD_SAFE) && \
    defined(HAVE_GETSERVBYNAME_R) && \
    (defined(GETSERVBYNAME_R_GLIBC2) || defined(GETSERVBYNAME_R_SOLARIS) || \
     defined(GETSERVBYNAME_R_OSF1))
    struct servent se;
#if defined(GETSERVBYNAME_R_OSF1)
    struct servent_data sed;

    memset(&sed, 0, sizeof(sed)); /* must zero fill before use */
#else
#if defined(GETSERVBYNAME_R_GLIBC2)
    struct servent *res;
#endif
    char buf[1024];
#endif
#else
    struct servent *se;
#endif

    if (servname == NULL)
        return APR_EINVAL;

#if APR_HAS_THREADS && !defined(GETSERVBYNAME_IS_THREAD_SAFE) && \
    defined(HAVE_GETSERVBYNAME_R) && \
    (defined(GETSERVBYNAME_R_GLIBC2) || defined(GETSERVBYNAME_R_SOLARIS) || \
     defined(GETSERVBYNAME_R_OSF1))
#if defined(GETSERVBYNAME_R_GLIBC2)
    if (getservbyname_r(servname, NULL,
                        &se, buf, sizeof(buf), &res) == 0 && res != NULL) {
        sockaddr->port = ntohs(res->s_port);
        sockaddr->servname = apr_pstrdup(sockaddr->pool, servname);
        sockaddr->sa.sin.sin_port = res->s_port;
        return APR_SUCCESS;
    }
#elif defined(GETSERVBYNAME_R_SOLARIS)
    if (getservbyname_r(servname, NULL, &se, buf, sizeof(buf)) != NULL) {
        sockaddr->port = ntohs(se.s_port);
        sockaddr->servname = apr_pstrdup(sockaddr->pool, servname);
        sockaddr->sa.sin.sin_port = se.s_port;
        return APR_SUCCESS;
    }
#elif defined(GETSERVBYNAME_R_OSF1)
    if (getservbyname_r(servname, NULL, &se, &sed) == 0) {
        sockaddr->port = ntohs(se.s_port);
        sockaddr->servname = apr_pstrdup(sockaddr->pool, servname);
        sockaddr->sa.sin.sin_port = se.s_port;
        return APR_SUCCESS;
    }
#endif
#else
    if ((se = getservbyname(servname, NULL)) != NULL){
        sockaddr->port = ntohs(se->s_port);
        sockaddr->servname = apr_pstrdup(sockaddr->pool, servname);
        sockaddr->sa.sin.sin_port = se->s_port;
        return APR_SUCCESS;
    }
#endif
    return APR_ENOENT;
}

#define V4MAPPED_EQUAL(a,b)                                   \
((a)->sa.sin.sin_family == AF_INET &&                         \
 (b)->sa.sin.sin_family == AF_INET6 &&                        \
 IN6_IS_ADDR_V4MAPPED((struct in6_addr *)(b)->ipaddr_ptr) &&  \
 !memcmp((a)->ipaddr_ptr,                                     \
         &((struct in6_addr *)(b)->ipaddr_ptr)->s6_addr[12],  \
         (a)->ipaddr_len))

APR_DECLARE(int) apr_sockaddr_equal(const apr_sockaddr_t *addr1,
                                    const apr_sockaddr_t *addr2)
{
    if (addr1->ipaddr_len == addr2->ipaddr_len &&
        !memcmp(addr1->ipaddr_ptr, addr2->ipaddr_ptr, addr1->ipaddr_len)) {
        return 1;
    }
#if APR_HAVE_IPV6
    if (V4MAPPED_EQUAL(addr1, addr2)) {
        return 1;
    }
    if (V4MAPPED_EQUAL(addr2, addr1)) {
        return 1;
    }
#endif
    return 0; /* not equal */
}

static apr_status_t parse_network(apr_ipsubnet_t *ipsub, const char *network)
{
    /* legacy syntax for ip addrs: a.b.c. ==> a.b.c.0/24 for example */
    int shift;
    char *s, *t;
    int octet;
    char buf[sizeof "255.255.255.255"];

    if (strlen(network) < sizeof buf) {
        strcpy(buf, network);
    }
    else {
        return APR_EBADIP;
    }

    /* parse components */
    s = buf;
    ipsub->sub[0] = 0;
    ipsub->mask[0] = 0;
    shift = 24;
    while (*s) {
        t = s;
        if (!apr_isdigit(*t)) {
            return APR_EBADIP;
        }
        while (apr_isdigit(*t)) {
            ++t;
        }
        if (*t == '.') {
            *t++ = 0;
        }
        else if (*t) {
            return APR_EBADIP;
        }
        if (shift < 0) {
            return APR_EBADIP;
        }
        octet = atoi(s);
        if (octet < 0 || octet > 255) {
            return APR_EBADIP;
        }
        ipsub->sub[0] |= octet << shift;
        ipsub->mask[0] |= 0xFFUL << shift;
        s = t;
        shift -= 8;
    }
    ipsub->sub[0] = ntohl(ipsub->sub[0]);
    ipsub->mask[0] = ntohl(ipsub->mask[0]);
    ipsub->family = AF_INET;
    return APR_SUCCESS;
}

/* return values:
 * APR_EINVAL     not an IP address; caller should see if it is something else
 * APR_BADIP      IP address portion is is not valid
 * APR_BADMASK    mask portion is not valid
 */

static apr_status_t parse_ip(apr_ipsubnet_t *ipsub, const char *ipstr, int network_allowed)
{
    /* supported flavors of IP:
     *
     * . IPv6 numeric address string (e.g., "fe80::1")
     * 
     *   IMPORTANT: Don't store IPv4-mapped IPv6 address as an IPv6 address.
     *
     * . IPv4 numeric address string (e.g., "127.0.0.1")
     *
     * . IPv4 network string (e.g., "9.67")
     *
     *   IMPORTANT: This network form is only allowed if network_allowed is on.
     */
    int rc;

#if APR_HAVE_IPV6
    rc = apr_inet_pton(AF_INET6, ipstr, ipsub->sub);
    if (rc == 1) {
        if (IN6_IS_ADDR_V4MAPPED((struct in6_addr *)ipsub->sub)) {
            /* apr_ipsubnet_test() assumes that we don't create IPv4-mapped IPv6
             * addresses; this of course forces the user to specify IPv4 addresses
             * in a.b.c.d style instead of ::ffff:a.b.c.d style.
             */
            return APR_EBADIP;
        }
        ipsub->family = AF_INET6;
    }
    else
#endif
    {
        rc = apr_inet_pton(AF_INET, ipstr, ipsub->sub);
        if (rc == 1) {
            ipsub->family = AF_INET;
        }
    }
    if (rc != 1) {
        if (network_allowed) {
            return parse_network(ipsub, ipstr);
        }
        else {
            return APR_EBADIP;
        }
    }
    return APR_SUCCESS;
}

static int looks_like_ip(const char *ipstr)
{
    if (strchr(ipstr, ':')) {
        /* definitely not a hostname; assume it is intended to be an IPv6 address */
        return 1;
    }

    /* simple IPv4 address string check */
    while ((*ipstr == '.') || apr_isdigit(*ipstr))
        ipstr++;
    return (*ipstr == '\0');
}

static void fix_subnet(apr_ipsubnet_t *ipsub)
{
    /* in case caller specified more bits in network address than are
     * valid according to the mask, turn off the extra bits
     */
    int i;

    for (i = 0; i < sizeof ipsub->mask / sizeof(apr_int32_t); i++) {
        ipsub->sub[i] &= ipsub->mask[i];
    }
}

/* be sure not to store any IPv4 address as a v4-mapped IPv6 address */
APR_DECLARE(apr_status_t) apr_ipsubnet_create(apr_ipsubnet_t **ipsub, const char *ipstr, 
                                              const char *mask_or_numbits, apr_pool_t *p)
{
    apr_status_t rv;
    char *endptr;
    long bits, maxbits = 32;

    /* filter out stuff which doesn't look remotely like an IP address; this helps 
     * callers like mod_access which have a syntax allowing hostname or IP address;
     * APR_EINVAL tells the caller that it was probably not intended to be an IP
     * address
     */
    if (!looks_like_ip(ipstr)) {
        return APR_EINVAL;
    }

    *ipsub = apr_pcalloc(p, sizeof(apr_ipsubnet_t));

    /* assume ipstr is an individual IP address, not a subnet */
    memset((*ipsub)->mask, 0xFF, sizeof (*ipsub)->mask);

    rv = parse_ip(*ipsub, ipstr, mask_or_numbits == NULL);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    if (mask_or_numbits) {
#if APR_HAVE_IPV6
        if ((*ipsub)->family == AF_INET6) {
            maxbits = 128
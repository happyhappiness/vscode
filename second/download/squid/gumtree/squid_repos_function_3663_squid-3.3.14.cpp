void
squid_res_setservers(int reset)
{
#if _SQUID_FREEBSD_ && defined(_SQUID_RES_NSADDR6_COUNT)
    /* Only seems to be valid on FreeBSD 5.5 where _res_ext was provided without an ns6addr counter! */
    /* Gone again on FreeBSD 6.2 along with _res_ext itself in any form. */
    int ns6count = 0;
#endif
#if HAVE_RES_INIT && defined(_SQUID_RES_NSADDR_LIST)
    extern char *optarg;
#endif

#if HAVE_RES_INIT && (defined(_SQUID_RES_NSADDR_LIST) || defined(_SQUID_RES_NSADDR6_LIST))

    if (reset == 0) {
#if defined(_SQUID_RES_NSADDR_COUNT)
        _SQUID_RES_NSADDR_COUNT = 0;
        /* because I don't trust the nscount super-count entirely, make sure these are ALL invalid */
        memset(_SQUID_RES_NSADDR_LIST, 0, sizeof(struct sockaddr_in)*MAXNS);
#endif
#if defined(_SQUID_RES_NSADDR6_COUNT)
        _SQUID_RES_NSADDR6_COUNT = 0;
#endif
    }

    /* AYJ:
     *  I experimented with all the permutations of mixed/unmixed nscount/nscount6 IPv4/IPv6/Both/invalid
     *
     *  I'm not sure if splitting them really helps.
     *  I've seen no evidence of IPv4 resolver *ever* being used when some IPv6 are set (or not even)
     *  BUT, have seen segfault when IPv4 is added to NSADDR6 list (_res._u._ext).
     *  It also appears to not do ANY lookup when _res.nscount==0.
     *
     *  BUT, even if _res.nsaddrs is memset to NULL, it resolves IFF IPv6 set in _ext.
     *
     *  SO, am splitting the IPv4/v6 into the seperate _res fields
     *      and making nscount a total of IPv4+IPv6 /w nscount6 the IPv6 sub-counter
     *	ie. nscount = count(NSv4)+count(NSv6) & nscount6 = count(NSv6)
     *
     * If ANYONE knows better please let us know.
     */
    struct addrinfo hints;
    memset(&hints, '\0', sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_NUMERICHOST; // prevent repeated DNS lookups!
    struct addrinfo *AI = NULL;
    if ( getaddrinfo(optarg, NULL, &hints, &AI) != 0) {
        fprintf(stderr, "%s appears to be a bad nameserver FQDN/IP.\n",optarg);
    } else if ( AI->ai_family == AF_INET ) {
        if (_SQUID_RES_NSADDR_COUNT == MAXNS) {
            fprintf(stderr, "Too many -s options, only %d are allowed\n", MAXNS);
        } else {
            _SQUID_RES_NSADDR_LIST[_SQUID_RES_NSADDR_COUNT] = _SQUID_RES_NSADDR_LIST[0];
            memcpy(&_SQUID_RES_NSADDR_LIST[_SQUID_RES_NSADDR_COUNT++].sin_addr, &((struct sockaddr_in*)AI->ai_addr)->sin_addr, sizeof(struct in_addr));
        }
    } else if ( AI->ai_family == AF_INET6 ) {
#if USE_IPV6 && defined(_SQUID_RES_NSADDR6_LIST)
        /* because things NEVER seem to resolve in tests without _res.nscount being a total. */
        if (_SQUID_RES_NSADDR_COUNT == MAXNS) {
            fprintf(stderr, "Too many -s options, only %d are allowed\n", MAXNS);
        } else {
            ++ _SQUID_RES_NSADDR_COUNT;
            memcpy(&_SQUID_RES_NSADDR6_LIST(_SQUID_RES_NSADDR6_COUNT++), &((struct sockaddr_in6*)AI->ai_addr)->sin6_addr, sizeof(struct in6_addr));
        }
#else
        fprintf(stderr, "IPv6 nameservers not supported on this resolver\n");
#endif
    }
    if (AI != NULL)
        freeaddrinfo(AI);

#else /* !HAVE_RES_INIT || !defined(_SQUID_RES_NSADDR_LIST) */

    fprintf(stderr, "-s is not supported on this resolver\n");

#endif /* HAVE_RES_INIT */
}
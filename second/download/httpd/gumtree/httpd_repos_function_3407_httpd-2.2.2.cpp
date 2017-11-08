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
        if (ai->ai_family != AF_INET && ai->ai_family != AF_INET6) {
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
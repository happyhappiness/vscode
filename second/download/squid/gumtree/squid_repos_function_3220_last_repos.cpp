bool
Ip::Address::lookupHostIP(const char *s, bool nodns)
{
    struct addrinfo want;
    memset(&want, 0, sizeof(struct addrinfo));
    if (nodns) {
        want.ai_flags = AI_NUMERICHOST; // prevent actual DNS lookups!
    }

    int err = 0;
    struct addrinfo *res = NULL;
    if ( (err = getaddrinfo(s, NULL, &want, &res)) != 0) {
        debugs(14,3, HERE << "Given Non-IP '" << s << "': " << gai_strerror(err) );
        /* free the memory getaddrinfo() dynamically allocated. */
        if (res)
            freeaddrinfo(res);
        return false;
    }

    struct addrinfo *resHead = res; // we need to free the whole list later
    if (!Ip::EnableIpv6) {
        // if we are IPv6-disabled, use first-IPv4 instead of first-IP.
        struct addrinfo *maybeIpv4 = res;
        while (maybeIpv4) {
            if (maybeIpv4->ai_family == AF_INET)
                break;
            maybeIpv4 = maybeIpv4->ai_next;
        }
        if (maybeIpv4 != NULL)
            res = maybeIpv4;
        // else IPv6-only host, let the caller deal with first-IP anyway.
    }

    /*
     *  NP: =(sockaddr_*) may alter the port. we don't want that.
     *      all we have been given as input was an IPA.
     */
    short portSaved = port();
    operator=(*res);
    port(portSaved);

    /* free the memory getaddrinfo() dynamically allocated. */
    freeaddrinfo(resHead);
    return true;
}
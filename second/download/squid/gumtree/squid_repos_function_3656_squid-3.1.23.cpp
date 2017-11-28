bool IpAddress::LookupHostIP(const char *s, bool nodns)
{
    int err = 0;

    short port = 0;

    struct addrinfo *res = NULL;

    struct addrinfo want;

    memset(&want, 0, sizeof(struct addrinfo));
    if (nodns) {
        want.ai_flags = AI_NUMERICHOST; // prevent actual DNS lookups!
    }
#if 0
    else if (!Ip::EnableIpv6)
        want.ai_family = AF_INET;  // maybe prevent IPv6 DNS lookups.
#endif

    if ( (err = xgetaddrinfo(s, NULL, &want, &res)) != 0) {
        debugs(14,3, HERE << "Given Non-IP '" << s << "': " << xgai_strerror(err) );
        /* free the memory xgetaddrinfo() dynamically allocated. */
        if (res) {
            xfreeaddrinfo(res);
            res = NULL;
        }
        return false;
    }

    /*
     *  NP: =(sockaddr_*) may alter the port. we don't want that.
     *      all we have been given as input was an IPA.
     */
    port = GetPort();
    operator=(*res);
    SetPort(port);

    /* free the memory xgetaddrinfo() dynamically allocated. */
    xfreeaddrinfo(res);

    res = NULL;

    return true;
}
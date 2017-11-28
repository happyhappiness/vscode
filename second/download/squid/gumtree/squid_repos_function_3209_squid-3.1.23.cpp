int
urlCheckRequest(const HttpRequest * r)
{
    int rc = 0;
    /* protocol "independent" methods
     *
     * actually these methods are specific to HTTP:
     * they are methods we recieve on our HTTP port,
     * and if we had a FTP listener would not be relevant
     * there.
     *
     * So, we should delegate them to HTTP. The problem is that we
     * do not have a default protocol from the client side of HTTP.
     */

    if (r->method == METHOD_CONNECT)
        return 1;

    // we support OPTIONS and TRACE directed at us (with a 501 reply, for now)
    // we also support forwarding OPTIONS and TRACE, except for the *-URI ones
    if (r->method == METHOD_OPTIONS || r->method == METHOD_TRACE)
        return (r->header.getInt64(HDR_MAX_FORWARDS) == 0 || r->urlpath != "*");

    if (r->method == METHOD_PURGE)
        return 1;

    /* does method match the protocol? */
    switch (r->protocol) {

    case PROTO_URN:

    case PROTO_HTTP:

    case PROTO_CACHEOBJ:
        rc = 1;
        break;

    case PROTO_FTP:

        if (r->method == METHOD_PUT)
            rc = 1;

    case PROTO_GOPHER:

    case PROTO_WAIS:

    case PROTO_WHOIS:
        if (r->method == METHOD_GET)
            rc = 1;
        else if (r->method == METHOD_HEAD)
            rc = 1;

        break;

    case PROTO_HTTPS:
#ifdef USE_SSL

        rc = 1;

        break;

#else
        /*
        * Squid can't originate an SSL connection, so it should
        * never receive an "https:" URL.  It should always be
        * CONNECT instead.
        */
        rc = 0;

#endif

    default:
        break;
    }

    return rc;
}
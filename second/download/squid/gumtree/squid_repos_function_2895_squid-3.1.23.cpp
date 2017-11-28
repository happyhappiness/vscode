bool
HttpRequest::cacheable() const
{
    if (protocol == PROTO_HTTP)
        return httpCachable(method);

    /*
     * The below looks questionable: what non HTTP protocols use connect,
     * trace, put and post? RC
     */

    if (!method.isCacheble())
        return false;

    /*
     * XXX POST may be cached sometimes.. ignored
     * for now
     */
    if (protocol == PROTO_GOPHER)
        return gopherCachable(this);

    if (protocol == PROTO_CACHEOBJ)
        return false;

    return true;
}
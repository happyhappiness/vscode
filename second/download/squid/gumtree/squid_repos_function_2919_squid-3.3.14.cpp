bool
HttpRequest::cacheable() const
{
    // Intercepted request with Host: header which cannot be trusted.
    // Because it failed verification, or someone bypassed the security tests
    // we cannot cache the reponse for sharing between clients.
    // TODO: update cache to store for particular clients only (going to same Host: and destination IP)
    if (!flags.hostVerified && (flags.intercepted || flags.spoofClientIp))
        return false;

    if (protocol == AnyP::PROTO_HTTP)
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
    if (protocol == AnyP::PROTO_GOPHER)
        return gopherCachable(this);

    if (protocol == AnyP::PROTO_CACHE_OBJECT)
        return false;

    return true;
}
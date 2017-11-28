static int
clientHierarchical(ClientHttpRequest * http)
{
    const char *url = http->uri;
    HttpRequest *request = http->request;
    HttpRequestMethod method = request->method;
    const wordlist *p = NULL;

    // intercepted requests MUST NOT (yet) be sent to peers unless verified
    if (!request->flags.hostVerified && (request->flags.intercepted || request->flags.spoofClientIp))
        return 0;

    /*
     * IMS needs a private key, so we can use the hierarchy for IMS only if our
     * neighbors support private keys
     */

    if (request->flags.ims && !neighbors_do_private_keys)
        return 0;

    /*
     * This is incorrect: authenticating requests can be sent via a hierarchy
     * (they can even be cached if the correct headers are set on the reply)
     */
    if (request->flags.auth)
        return 0;

    if (method == METHOD_TRACE)
        return 1;

    if (method != METHOD_GET)
        return 0;

    /* scan hierarchy_stoplist */
    for (p = Config.hierarchy_stoplist; p; p = p->next)
        if (strstr(url, p->key))
            return 0;

    if (request->flags.loopDetected)
        return 0;

    if (request->protocol == AnyP::PROTO_HTTP)
        return httpCachable(method);

    if (request->protocol == AnyP::PROTO_GOPHER)
        return gopherCachable(request);

    if (request->protocol == AnyP::PROTO_CACHE_OBJECT)
        return 0;

    return 1;
}
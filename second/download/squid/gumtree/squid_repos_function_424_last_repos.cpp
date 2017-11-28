static int
clientHierarchical(ClientHttpRequest * http)
{
    HttpRequest *request = http->request;
    HttpRequestMethod method = request->method;

    // intercepted requests MUST NOT (yet) be sent to peers unless verified
    if (!request->flags.hostVerified && (request->flags.intercepted || request->flags.interceptTproxy))
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

    if (method == Http::METHOD_TRACE)
        return 1;

    if (method != Http::METHOD_GET)
        return 0;

    if (request->flags.loopDetected)
        return 0;

    if (request->url.getScheme() == AnyP::PROTO_HTTP)
        return method.respMaybeCacheable();

    if (request->url.getScheme() == AnyP::PROTO_GOPHER)
        return gopherCachable(request);

    if (request->url.getScheme() == AnyP::PROTO_CACHE_OBJECT)
        return 0;

    return 1;
}
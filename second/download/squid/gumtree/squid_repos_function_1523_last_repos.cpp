int
peerHTTPOkay(const CachePeer * p, HttpRequest * request)
{
    if (!peerCanOpenMore(p) && !peerHasConnAvailable(p))
        return 0;

    if (!peerAllowedToUse(p, request))
        return 0;

    if (!neighborUp(p))
        return 0;

    return 1;
}
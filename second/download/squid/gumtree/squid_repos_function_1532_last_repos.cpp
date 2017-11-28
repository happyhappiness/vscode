CachePeer *
getDefaultParent(HttpRequest * request)
{
    CachePeer *p = NULL;

    for (p = Config.peers; p; p = p->next) {
        if (neighborType(p, request->url) != PEER_PARENT)
            continue;

        if (!p->options.default_parent)
            continue;

        if (!peerHTTPOkay(p, request))
            continue;

        debugs(15, 3, "getDefaultParent: returning " << p->host);

        return p;
    }

    debugs(15, 3, "getDefaultParent: returning NULL");
    return NULL;
}
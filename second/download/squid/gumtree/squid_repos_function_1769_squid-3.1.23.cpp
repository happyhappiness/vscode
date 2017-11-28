peer *
getFirstUpParent(HttpRequest * request)
{
    peer *p = NULL;

    for (p = Config.peers; p; p = p->next) {
        if (!neighborUp(p))
            continue;

        if (neighborType(p, request) != PEER_PARENT)
            continue;

        if (!peerHTTPOkay(p, request))
            continue;

        break;
    }

    debugs(15, 3, "getFirstUpParent: returning " << (p ? p->host : "NULL"));
    return p;
}
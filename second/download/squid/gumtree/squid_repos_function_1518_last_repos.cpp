bool
peerAllowedToUse(const CachePeer * p, HttpRequest * request)
{

    assert(request != NULL);

    if (neighborType(p, request->url) == PEER_SIBLING) {
#if PEER_MULTICAST_SIBLINGS
        if (p->type == PEER_MULTICAST && p->options.mcast_siblings &&
                (request->flags.noCache || request->flags.refresh || request->flags.loopDetected || request->flags.needValidation))
            debugs(15, 2, "peerAllowedToUse(" << p->name << ", " << request->url.authority() << ") : multicast-siblings optimization match");
#endif
        if (request->flags.noCache)
            return false;

        if (request->flags.refresh)
            return false;

        if (request->flags.loopDetected)
            return false;

        if (request->flags.needValidation)
            return false;
    }

    // CONNECT requests are proxy requests. Not to be forwarded to origin servers.
    // Unless the destination port matches, in which case we MAY perform a 'DIRECT' to this CachePeer.
    if (p->options.originserver && request->method == Http::METHOD_CONNECT && request->url.port() != p->http_port)
        return false;

    if (p->access == NULL)
        return true;

    ACLFilledChecklist checklist(p->access, request, NULL);

    return checklist.fastCheck().allowed();
}
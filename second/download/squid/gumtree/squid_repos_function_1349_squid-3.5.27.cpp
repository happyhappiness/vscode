static void
peerGetSomeParent(ps_state * ps)
{
    CachePeer *p;
    HttpRequest *request = ps->request;
    hier_code code = HIER_NONE;
    debugs(44, 3, request->method << ' ' << request->GetHost());

    if (ps->direct == DIRECT_YES)
        return;

    if ((p = peerSourceHashSelectParent(request))) {
        code = SOURCEHASH_PARENT;
#if USE_AUTH
    } else if ((p = peerUserHashSelectParent(request))) {
        code = USERHASH_PARENT;
#endif
    } else if ((p = carpSelectParent(request))) {
        code = CARP;
    } else if ((p = getRoundRobinParent(request))) {
        code = ROUNDROBIN_PARENT;
    } else if ((p = getWeightedRoundRobinParent(request))) {
        code = ROUNDROBIN_PARENT;
    } else if ((p = getFirstUpParent(request))) {
        code = FIRSTUP_PARENT;
    } else if ((p = getDefaultParent(request))) {
        code = DEFAULT_PARENT;
    }

    if (code != HIER_NONE) {
        debugs(44, 3, "peerSelect: " << hier_code_str[code] << "/" << p->host);
        peerAddFwdServer(&ps->servers, p, code);
    }
}
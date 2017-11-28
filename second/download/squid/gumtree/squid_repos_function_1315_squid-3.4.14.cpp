static void
peerGetAllParents(ps_state * ps)
{
    CachePeer *p;
    HttpRequest *request = ps->request;
    /* Add all alive parents */

    for (p = Config.peers; p; p = p->next) {
        /* XXX: neighbors.c lacks a public interface for enumerating
         * parents to a request so we have to dig some here..
         */

        if (neighborType(p, request) != PEER_PARENT)
            continue;

        if (!peerHTTPOkay(p, request))
            continue;

        debugs(15, 3, "peerGetAllParents: adding alive parent " << p->host);

        peerAddFwdServer(&ps->servers, p, ANY_OLD_PARENT);
    }

    /* XXX: should add dead parents here, but it is currently
     * not possible to find out which parents are dead or which
     * simply are not configured to handle the request.
     */
    /* Add default parent as a last resort */
    if ((p = getDefaultParent(request))) {
        peerAddFwdServer(&ps->servers, p, DEFAULT_PARENT);
    }
}
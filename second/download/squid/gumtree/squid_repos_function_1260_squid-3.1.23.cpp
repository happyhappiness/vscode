static void
peerSelectPinned(ps_state * ps)
{
    HttpRequest *request = ps->request;
    peer *peer;
    if (!request->pinnedConnection())
        return;
    peer = request->pinnedConnection()->pinnedPeer();
    if (request->pinnedConnection()->validatePinnedConnection(request, peer) != -1) {
        if (peer && peerAllowedToUse(peer, request)) {
            peerAddFwdServer(&ps->servers, peer, PINNED);
            if (ps->entry)
                ps->entry->ping_status = PING_DONE;     /* Skip ICP */
        } else if (!peer && ps->direct != DIRECT_NO) {
            peerAddFwdServer(&ps->servers, NULL, PINNED);
            if (ps->entry)
                ps->entry->ping_status = PING_DONE;     /* Skip ICP */
        }
    }
}
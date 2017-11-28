static void
peerSelectPinned(ps_state * ps)
{
    HttpRequest *request = ps->request;
    if (!request->pinnedConnection())
        return;
    CachePeer *pear = request->pinnedConnection()->pinnedPeer();
    if (Comm::IsConnOpen(request->pinnedConnection()->validatePinnedConnection(request, pear))) {
        if (pear && peerAllowedToUse(pear, request)) {
            peerAddFwdServer(&ps->servers, pear, PINNED);
            if (ps->entry)
                ps->entry->ping_status = PING_DONE;     /* Skip ICP */
        } else if (!pear && ps->direct != DIRECT_NO) {
            peerAddFwdServer(&ps->servers, NULL, PINNED);
            if (ps->entry)
                ps->entry->ping_status = PING_DONE;     /* Skip ICP */
        }
    }
}
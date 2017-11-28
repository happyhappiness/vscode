static void
peerGetSomeNeighborReplies(ps_state * ps)
{
    HttpRequest *request = ps->request;
    CachePeer *p = NULL;
    hier_code code = HIER_NONE;
    assert(ps->entry->ping_status == PING_WAITING);
    assert(ps->direct != DIRECT_YES);

    if (peerCheckNetdbDirect(ps)) {
        code = CLOSEST_DIRECT;
        debugs(44, 3, "peerSelect: " << hier_code_str[code] << "/" << request->GetHost());
        peerAddFwdServer(&ps->servers, NULL, code);
        return;
    }

    if ((p = ps->hit)) {
        code = ps->hit_type == PEER_PARENT ? PARENT_HIT : SIBLING_HIT;
    } else {
        if (!ps->closest_parent_miss.IsAnyAddr()) {
            p = whichPeer(ps->closest_parent_miss);
            code = CLOSEST_PARENT_MISS;
        } else if (!ps->first_parent_miss.IsAnyAddr()) {
            p = whichPeer(ps->first_parent_miss);
            code = FIRST_PARENT_MISS;
        }
    }
    if (p && code != HIER_NONE) {
        debugs(44, 3, "peerSelect: " << hier_code_str[code] << "/" << p->host);
        peerAddFwdServer(&ps->servers, p, code);
    }
}
static void
peerHandleHtcpReply(peer * p, peer_t type, htcpReplyData * htcp, void *data)
{
    ps_state *psstate = (ps_state *)data;
    debugs(44, 3, "peerHandleHtcpReply: " <<
           (htcp->hit ? "HIT" : "MISS") << " " <<
           psstate->entry->url()  );
    psstate->ping.n_recv++;

    if (htcp->hit) {
        psstate->hit = p;
        psstate->hit_type = type;
        peerSelectFoo(psstate);
        return;
    }

    if (type == PEER_PARENT)
        peerHtcpParentMiss(p, htcp, psstate);

    if (psstate->ping.n_recv < psstate->ping.n_replies_expected)
        return;

    peerSelectFoo(psstate);
}
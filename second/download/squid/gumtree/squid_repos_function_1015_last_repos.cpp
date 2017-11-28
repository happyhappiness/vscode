static void
peerHandleIcpReply(CachePeer * p, peer_t type, icp_common_t * header, void *data)
{
    ps_state *psstate = (ps_state *)data;
    icp_opcode op = header->getOpCode();
    debugs(44, 3, "peerHandleIcpReply: " << icp_opcode_str[op] << " " << psstate->url()  );
#if USE_CACHE_DIGESTS && 0
    /* do cd lookup to count false misses */

    if (p && request)
        peerNoteDigestLookup(request, p,
                             peerDigestLookup(p, request, psstate->entry));

#endif

    ++ psstate->ping.n_recv;

    if (op == ICP_MISS || op == ICP_DECHO) {
        if (type == PEER_PARENT)
            peerIcpParentMiss(p, header, psstate);
    } else if (op == ICP_HIT) {
        psstate->hit = p;
        psstate->hit_type = type;
        peerSelectFoo(psstate);
        return;
    }

    if (psstate->ping.n_recv < psstate->ping.n_replies_expected)
        return;

    peerSelectFoo(psstate);
}
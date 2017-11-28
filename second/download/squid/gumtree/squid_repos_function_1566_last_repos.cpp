static void
peerCountHandleIcpReply(CachePeer * p, peer_t, AnyP::ProtocolType proto, void *, void *data)
{
    ps_state *psstate = (ps_state *)data;
    StoreEntry *fake = psstate->entry;
    assert(fake);
    MemObject *mem = fake->mem_obj;
    assert(mem);
    int rtt = tvSubMsec(mem->start_ping, current_time);
    assert(proto == AnyP::PROTO_ICP);
    ++ psstate->ping.n_recv;
    int rtt_av_factor = RTT_AV_FACTOR;

    if (p->options.weighted_roundrobin)
        rtt_av_factor = RTT_BACKGROUND_AV_FACTOR;

    p->stats.rtt = Math::intAverage(p->stats.rtt, rtt, psstate->ping.n_recv, rtt_av_factor);
}
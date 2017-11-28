static void
peerCountHandleIcpReply(peer * p, peer_t type, protocol_t proto, void *hdrnotused, void *data)
{
    int rtt_av_factor;

    ps_state *psstate = (ps_state *)data;
    StoreEntry *fake = psstate->entry;
    MemObject *mem = fake->mem_obj;
    int rtt = tvSubMsec(mem->start_ping, current_time);
    assert(proto == PROTO_ICP);
    assert(fake);
    assert(mem);
    psstate->ping.n_recv++;
    rtt_av_factor = RTT_AV_FACTOR;

    if (p->options.weighted_roundrobin)
        rtt_av_factor = RTT_BACKGROUND_AV_FACTOR;

    p->stats.rtt = Math::intAverage(p->stats.rtt, rtt, psstate->ping.n_recv, rtt_av_factor);
}
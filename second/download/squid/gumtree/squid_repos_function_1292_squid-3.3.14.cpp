static int
peerCheckNetdbDirect(ps_state * psstate)
{
#if USE_ICMP
    CachePeer *p;
    int myrtt;
    int myhops;

    if (psstate->direct == DIRECT_NO)
        return 0;

    /* base lookup on RTT and Hops if ICMP NetDB is enabled. */

    myrtt = netdbHostRtt(psstate->request->GetHost());

    debugs(44, 3, "peerCheckNetdbDirect: MY RTT = " << myrtt << " msec");
    debugs(44, 3, "peerCheckNetdbDirect: minimum_direct_rtt = " << Config.minDirectRtt << " msec");

    if (myrtt && myrtt <= Config.minDirectRtt)
        return 1;

    myhops = netdbHostHops(psstate->request->GetHost());

    debugs(44, 3, "peerCheckNetdbDirect: MY hops = " << myhops);
    debugs(44, 3, "peerCheckNetdbDirect: minimum_direct_hops = " << Config.minDirectHops);

    if (myhops && myhops <= Config.minDirectHops)
        return 1;

    p = whichPeer(psstate->closest_parent_miss);

    if (p == NULL)
        return 0;

    debugs(44, 3, "peerCheckNetdbDirect: closest_parent_miss RTT = " << psstate->ping.p_rtt << " msec");

    if (myrtt && myrtt <= psstate->ping.p_rtt)
        return 1;

#endif /* USE_ICMP */

    return 0;
}
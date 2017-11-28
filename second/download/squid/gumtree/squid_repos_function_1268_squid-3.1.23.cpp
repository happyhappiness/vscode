static void
peerIcpParentMiss(peer * p, icp_common_t * header, ps_state * ps)
{
    int rtt;

#if USE_ICMP
    if (Config.onoff.query_icmp) {
        if (header->flags & ICP_FLAG_SRC_RTT) {
            rtt = header->pad & 0xFFFF;
            int hops = (header->pad >> 16) & 0xFFFF;

            if (rtt > 0 && rtt < 0xFFFF)
                netdbUpdatePeer(ps->request, p, rtt, hops);

            if (rtt && (ps->ping.p_rtt == 0 || rtt < ps->ping.p_rtt)) {
                ps->closest_parent_miss = p->in_addr;
                ps->ping.p_rtt = rtt;
            }
        }
    }
#endif /* USE_ICMP */

    /* if closest-only is set, then don't allow FIRST_PARENT_MISS */
    if (p->options.closest_only)
        return;

    /* set FIRST_MISS if there is no CLOSEST parent */
    if (!ps->closest_parent_miss.IsAnyAddr())
        return;

    rtt = (tvSubMsec(ps->ping.start, current_time) - p->basetime) / p->weight;

    if (rtt < 1)
        rtt = 1;

    if (ps->first_parent_miss.IsAnyAddr() || rtt < ps->ping.w_rtt) {
        ps->first_parent_miss = p->in_addr;
        ps->ping.w_rtt = rtt;
    }
}
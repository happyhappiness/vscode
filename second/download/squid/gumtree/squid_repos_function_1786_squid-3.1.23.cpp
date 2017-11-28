static void
neighborAlive(peer * p, const MemObject * mem, const icp_common_t * header)
{
    peerAlive(p);
    p->stats.pings_acked++;

    if ((icp_opcode) header->opcode <= ICP_END)
        p->icp.counts[header->opcode]++;

    p->icp.version = (int) header->version;
}
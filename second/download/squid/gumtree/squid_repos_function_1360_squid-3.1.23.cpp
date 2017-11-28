void
_icp_common_t::handleReply(char *buf, IpAddress &from)
{
    if (neighbors_do_private_keys && reqnum == 0) {
        debugs(12, 0, "icpHandleIcpV2: Neighbor " << from << " returned reqnum = 0");
        debugs(12, 0, "icpHandleIcpV2: Disabling use of private keys");
        neighbors_do_private_keys = 0;
    }

    char *url = buf + sizeof(icp_common_t);
    debugs(12, 3, "icpHandleIcpV2: " << icp_opcode_str[opcode] << " from " << from << " for '" << url << "'");

    const cache_key *key = icpGetCacheKey(url, (int) reqnum);
    /* call neighborsUdpAck even if ping_status != PING_WAITING */
    neighborsUdpAck(key, this, from);
}
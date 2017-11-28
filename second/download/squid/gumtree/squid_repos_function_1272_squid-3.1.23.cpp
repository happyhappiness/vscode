static void
peerHandlePingReply(peer * p, peer_t type, protocol_t proto, void *pingdata, void *data)
{
    if (proto == PROTO_ICP)
        peerHandleIcpReply(p, type, (icp_common_t *)pingdata, data);

#if USE_HTCP

    else if (proto == PROTO_HTCP)
        peerHandleHtcpReply(p, type, (htcpReplyData *)pingdata, data);

#endif

    else
        debugs(44, 1, "peerHandlePingReply: unknown protocol_t " << proto);
}
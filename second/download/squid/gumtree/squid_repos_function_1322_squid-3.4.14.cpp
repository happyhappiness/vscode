static void
peerHandlePingReply(CachePeer * p, peer_t type, AnyP::ProtocolType proto, void *pingdata, void *data)
{
    if (proto == AnyP::PROTO_ICP)
        peerHandleIcpReply(p, type, (icp_common_t *)pingdata, data);

#if USE_HTCP

    else if (proto == AnyP::PROTO_HTCP)
        peerHandleHtcpReply(p, type, (HtcpReplyData *)pingdata, data);

#endif

    else
        debugs(44, DBG_IMPORTANT, "peerHandlePingReply: unknown protocol " << proto);
}
IpAddress
getOutgoingAddr(HttpRequest * request, struct peer *dst_peer)
{
    if (request && request->flags.spoof_client_ip) {
        if (!dst_peer || !dst_peer->options.no_tproxy)
            return request->client_addr;
        // else no tproxy today ...
    }

    if (!Config.accessList.outgoing_address) {
        return IpAddress(); // anything will do.
    }

    ACLFilledChecklist ch(NULL, request, NULL);
    ch.dst_peer = dst_peer;

    if (request) {
#if FOLLOW_X_FORWARDED_FOR
        if (Config.onoff.acl_uses_indirect_client)
            ch.src_addr = request->indirect_client_addr;
        else
#endif
            ch.src_addr = request->client_addr;
        ch.my_addr = request->my_addr;
    }

    return aclMapAddr(Config.accessList.outgoing_address, &ch);
}
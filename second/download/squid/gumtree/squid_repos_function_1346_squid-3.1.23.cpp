void
ICP2State::created(StoreEntry *newEntry)
{
    StoreEntry *entry = newEntry->isNull () ? NULL : newEntry;
    debugs(12, 5, "icpHandleIcpV2: OPCODE " << icp_opcode_str[header.opcode]);
    icp_opcode codeToSend;

    if (icpCheckUdpHit(entry, request)) {
        codeToSend = ICP_HIT;
    } else {
#if USE_ICMP
        if (Config.onoff.test_reachability && rtt == 0) {
            if ((rtt = netdbHostRtt(request->GetHost())) == 0)
                netdbPingSite(request->GetHost());
        }
#endif /* USE_ICMP */

        if (icpGetCommonOpcode() != ICP_ERR)
            codeToSend = icpGetCommonOpcode();
        else if (Config.onoff.test_reachability && rtt == 0)
            codeToSend = ICP_MISS_NOFETCH;
        else
            codeToSend = ICP_MISS;
    }

    icpCreateAndSend(codeToSend, flags, url, header.reqnum, src_rtt, fd, from);
    delete this;
}
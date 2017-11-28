void
ICP3State::created(StoreEntry *newEntry)
{
    StoreEntry *entry = newEntry->isNull () ? NULL : newEntry;
    debugs(12, 5, "icpHandleIcpV3: OPCODE " << icp_opcode_str[header.opcode]);
    icp_opcode codeToSend;

    if (icpCheckUdpHit(entry, request)) {
        codeToSend = ICP_HIT;
    } else if (icpGetCommonOpcode() == ICP_ERR)
        codeToSend = ICP_MISS;
    else
        codeToSend = icpGetCommonOpcode();

    icpCreateAndSend (codeToSend, 0, url, header.reqnum, 0, fd, from);

    delete this;
}
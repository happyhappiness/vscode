LogTags
icpLogFromICPCode(icp_opcode opcode)
{
    if (opcode == ICP_ERR)
        return LOG_UDP_INVALID;

    if (opcode == ICP_DENIED)
        return LOG_UDP_DENIED;

    if (opcode == ICP_HIT)
        return LOG_UDP_HIT;

    if (opcode == ICP_MISS)
        return LOG_UDP_MISS;

    if (opcode == ICP_MISS_NOFETCH)
        return LOG_UDP_MISS_NOFETCH;

    fatal("expected ICP opcode\n");

    return LOG_UDP_INVALID;
}
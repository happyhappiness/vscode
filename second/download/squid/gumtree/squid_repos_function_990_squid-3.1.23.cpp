void
icpHandleIcpV3(int fd, IpAddress&from, char *buf, int len)
{
    if (len <= 0) {
        debugs(12, 3, "icpHandleIcpV3: ICP message is too small");
        return;
    }

    icp_common_t header (buf, len);
    /*
     * Length field should match the number of bytes read
     */

    if (len != header.length) {
        debugs(12, 3, "icpHandleIcpV3: ICP message is too small");
        return;
    }

    switch (header.opcode) {

    case ICP_QUERY:
        doV3Query(fd, from, buf, header);
        break;

    case ICP_HIT:

    case ICP_DECHO:

    case ICP_MISS:

    case ICP_DENIED:

    case ICP_MISS_NOFETCH:
        header.handleReply(buf, from);
        break;

    case ICP_INVALID:

    case ICP_ERR:
        break;

    default:
        debugs(12, 0, "icpHandleIcpV3: UNKNOWN OPCODE: " << header.opcode << " from " << from);
        break;
    }
}
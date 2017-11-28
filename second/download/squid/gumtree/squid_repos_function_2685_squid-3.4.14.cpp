static ssize_t
htcpBuildOpData(char *buf, size_t buflen, htcpStuff * stuff)
{
    ssize_t off = 0;
    debugs(31, 3, "htcpBuildOpData: opcode " << htcpOpcodeStr[stuff->op]);

    switch (stuff->op) {

    case HTCP_TST:
        off = htcpBuildTstOpData(buf + off, buflen, stuff);
        break;

    case HTCP_CLR:
        off = htcpBuildClrOpData(buf + off, buflen, stuff);
        break;

    default:
        assert(0);
        break;
    }

    return off;
}
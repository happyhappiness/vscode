static void
htcpForwardClr(char *buf, int sz)
{
    CachePeer *p;

    for (p = Config.peers; p; p = p->next) {
        if (!p->options.htcp) {
            continue;
        }
        if (!p->options.htcp_forward_clr) {
            continue;
        }

        htcpSend(buf, sz, p->in_addr);
    }
}
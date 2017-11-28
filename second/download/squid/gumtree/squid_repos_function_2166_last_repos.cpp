void
htcpClosePorts(void)
{
    htcpSocketShutdown();

    if (htcpOutgoingConn != NULL) {
        debugs(12, DBG_IMPORTANT, "Stop sending HTCP from " << htcpOutgoingConn->local);
        htcpOutgoingConn = NULL;
    }
}
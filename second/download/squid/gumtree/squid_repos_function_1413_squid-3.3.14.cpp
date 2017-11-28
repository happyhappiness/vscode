void
icpClosePorts(void)
{
    icpConnectionShutdown();

    if (icpOutgoingConn != NULL) {
        debugs(12, DBG_IMPORTANT, "Stop sending ICP from " << icpOutgoingConn->local);
        icpOutgoingConn = NULL;
    }
}
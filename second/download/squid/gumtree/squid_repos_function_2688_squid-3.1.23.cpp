void
htcpSocketClose(void)
{
    htcpSocketShutdown();

    if (htcpOutSocket > -1) {
        debugs(12, 1, "FD " << htcpOutSocket << " Closing HTCP socket");
        comm_close(htcpOutSocket);
        htcpOutSocket = -1;
    }
}
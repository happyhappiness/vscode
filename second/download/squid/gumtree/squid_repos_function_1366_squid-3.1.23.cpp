void
icpConnectionClose(void)
{
    icpConnectionShutdown();

    if (theOutIcpConnection > -1) {
        debugs(12, 1, "FD " << theOutIcpConnection << " Closing ICP connection");
        comm_close(theOutIcpConnection);
        theOutIcpConnection = -1;
    }
}